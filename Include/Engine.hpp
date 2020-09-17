/*
 * Copyright (c) 2020 Hani Ammar
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "Memory.hpp"

#ifndef QENTEM_ENGINE_H_
#define QENTEM_ENGINE_H_

namespace Qentem {

/*
 * A fast search class for nest/sub-matching.
 */
class Engine {
  public:
    Engine()               = delete;
    Engine(Engine &&)      = delete;
    Engine(const Engine &) = delete;
    Engine &operator=(Engine &&) = delete;
    Engine &operator=(const Engine &) = delete;
    ~Engine()                         = delete;
#ifdef QENTEM_SIMD_ENABLED_
    /*
     * Returns an the index of a character + 1.
     */
    static ULong FindOne(const char one_char, const char *content, ULong offset,
                         ULong end_before) noexcept {
        // TODO: Add 16 and 32-bit char
        if (offset < end_before) {
            const QMM_VAR_ m_pattern = QMM_SETONE_8_(one_char);

            do {
                const QMM_VAR_ m_content = QMM_LOAD_(
                    reinterpret_cast<const QMM_VAR_ *>(content + offset));

                const QMM_Number_T bits =
                    QMM_COMPARE_8_MASK_(m_pattern, m_content);

                if (bits != 0) {
                    const ULong index = (Platform::CTZL(bits) + offset + 1);

                    if (index > end_before) {
                        return 0;
                    }

                    return index;
                }

                offset += QMM_SIZE_;
            } while (offset < end_before);
        }

        return 0;
    }

    /*
     * Returns an the index of a pattern + the length of it.
     */
    static ULong Find(const char *pattern, UInt pattern_length,
                      const char *content, ULong offset,
                      ULong end_before) noexcept {
        if (pattern_length == 1) {
            return FindOne(*pattern, content, offset, end_before);
        }

        if (offset < end_before) {
            const QMM_VAR_ m_pattern_first = QMM_SETONE_8_(*pattern);
            const UInt     len_less_one    = (pattern_length - 1);
            const QMM_VAR_ m_pattern_last =
                QMM_SETONE_8_(pattern[len_less_one]);

            do {
                QMM_VAR_ m_content = QMM_LOAD_(
                    reinterpret_cast<const QMM_VAR_ *>(content + offset));
                QMM_Number_T bits =
                    QMM_COMPARE_8_MASK_(m_content, m_pattern_first);

                m_content = QMM_LOAD_(reinterpret_cast<const QMM_VAR_ *>(
                    content + offset + len_less_one));
                bits &= QMM_COMPARE_8_MASK_(m_content, m_pattern_last);

                while (bits != 0) {
                    const ULong index         = (Platform::CTZL(bits) + offset);
                    const ULong pattern_index = (index + pattern_length);

                    if (pattern_index > end_before) {
                        return 0;
                    }

                    if ((len_less_one == 1) ||
                        Memory::IsEqual(pattern, (content + index),
                                        len_less_one)) {
                        return pattern_index;
                    }

                    bits &= (bits - 1);
                }

                offset += QMM_SIZE_;
            } while (offset < end_before);
        }

        return 0;
    }
#else
    /*
     * Returns an the index of a character + 1.
     */
    template <typename Char_T_>
    static ULong FindOne(const Char_T_ one_char, const Char_T_ *content,
                         ULong offset, ULong end_before) noexcept {
        while (offset < end_before) {
            if (one_char == content[offset]) {
                return (offset + 1);
            }

            ++offset;
        }

        return 0;
    }

    /*
     * Returns an the index of a pattern + the length of it.
     */
    template <typename Char_T_>
    static ULong Find(const Char_T_ *pattern, UInt pattern_length,
                      const Char_T_ *content, ULong offset,
                      ULong end_before) noexcept {
        if (pattern_length == 1) {
            return FindOne(*pattern, content, offset, end_before);
        }

        --pattern_length;

        while (offset < end_before) {
            if (pattern[0] == content[offset]) {

                if ((offset + pattern_length) >= end_before) {
                    return 0;
                }

                if (pattern[pattern_length] ==
                    content[offset + pattern_length]) {
                    const ULong last_offset    = offset;
                    UInt        pattern_offset = 1;

                    ++offset;

                    while ((pattern_offset != pattern_length) &&
                           pattern[pattern_offset] == content[offset]) {
                        ++offset;
                        ++pattern_offset;
                    }

                    if (pattern_offset == pattern_length) {
                        return (offset + 1);
                    }

                    offset = last_offset;
                }
            }

            ++offset;
        }

        return 0;
    }
#endif

    /*
     * finds the head and the tail of a match and search aging inside the match
     * to see if it's Nested by itself or a custom expression.
     */
    template <typename Char_T_, typename Class_T_>
    static ULong FindNest(const Char_T_ *content, ULong offset,
                          ULong end_before, ULong max_end_before,
                          Class_T_ *caller) {
        ULong current_offset = offset;

        while (current_offset < end_before) {
            /*
             * ULong FindH(const Class_T_ *content, ULong offset, ULong
             * end_before)
             *
             * For finding the head
             */
            current_offset = caller->FindH(content, current_offset, end_before);

            if (current_offset == 0) {
                // The head hasn't been found
                break;
            }

            // Save the current offset for Found().
            const ULong start_offset = current_offset;
            // Makes sub-matching easy.
            ULong sub_offset = current_offset;

            /*
             * bool HasTail();
             *
             * This is invoked to check if the match has a second part/tail.
             * Like head: { and the tail is } or () or "" or < > ...etc.
             */
            if (caller->HasTail()) {
                do {
                    /*
                     * ULong FindT(const Class_T_ *content, ULong offset, ULong
                     *             end_before)
                     *
                     * For finding the tail
                     */
                    current_offset =
                        caller->FindT(content, current_offset, max_end_before);

                    if (current_offset == 0) {
                        /*
                         * void Failed()
                         *
                         * If the head of the match is found but not the tail,
                         * this function will be invoked.
                         */
                        caller->Failed();
                        return sub_offset;
                    }

                    /*
                     * ULong Nest(const Class_T_ *content, ULong offset, ULong
                     *            end_before, ULong max_end_before)
                     *
                     * This function is invoked everytime a match found, and
                     * should look like the first line that started the search.
                     * with the exception of setting different values; like
                     * passing a sub-container.
                     */
                    sub_offset = caller->Nest(content, sub_offset,
                                              current_offset, max_end_before);

                    if (current_offset > sub_offset) {
                        /*
                         * No sub-matches or none of them breaking this match,
                         * So stop and call this a match.
                         */
                        break;
                    }

                    /*
                     * If nest() returns a bigger offset than current_offset,
                     * then this match is not complete. Adjust the offset and
                     * keep looking.
                     */
                    current_offset = sub_offset;
                } while (current_offset != max_end_before);
            }

            /*
             * void Found(const Class_T_ *content, ULong offset, ULong
             *            end_before, ULong start_offset, ULong &current_offset)
             *
             * Once a full match is found (head & tail), the function will be
             * invoked. "current_offset" is referenced: it can be adjusted to
             * set the starting offset of the next search.
             */
            caller->Found(content, offset, end_before, start_offset,
                          current_offset);
        }

        // Return the location of the last match.
        return current_offset;
    }

    /*
     * If a search is about { ... }, and nest itself like:
     * {.{..{...}..}.}; then this function can be invoked from nest() to skip
     * inner brackets:
     *
     * return SkipInnerPatterns("{", 1, "}", 1,
     *                          content, offset, end_before, max_end_before);
     *
     * See Template::nest(...)
     */
    template <typename Char_T_>
    static ULong SkipInnerPatterns(const Char_T_ *start, UInt start_length,
                                   const Char_T_ *end, UInt end_length,
                                   const Char_T_ *content, ULong offset,
                                   ULong end_before,
                                   ULong max_end_before) noexcept {
        ULong last_offset = end_before;

        while (end_before < max_end_before) {
            UInt times = 0;

            do {
                offset = Find(start, start_length, content, offset, end_before);

                if (offset == 0) {
                    break;
                }

                ++times;
            } while (true);

            if (times == 0) {
                return end_before;
            }

            offset = end_before;
            // TODO: Use FindAll
            do {
                end_before =
                    Find(end, end_length, content, last_offset, max_end_before);

                if (end_before == 0) {
                    return last_offset;
                }

                last_offset = end_before;
                --times;
            } while (times != 0);
        }

        return last_offset;
    }
};

} // namespace Qentem

#endif
