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

#include "TestHelper.hpp"

#include "Unicode.hpp"

#ifndef QENTEM_UNICODE_TESTS_H_
#define QENTEM_UNICODE_TESTS_H_

namespace Qentem {
namespace Test {

static int TestToUTF8() {
    /*
     * HEX         UNICODE      BINARY
     * 0x0000      0            00000000
     * 0x003D      61           00111101
     * 0x007F      127          01111111
     *
     * 0x0080      128          11000010-10000000
     * 0x00A1      161          11000010-10100001
     * 0x07FF      2047         11011111-10111111
     *
     * 0x0800      2048         11100000-10100000-10000000
     * 0x08A7      2215         11100000-10100010-10100111
     * 0xFFFF      65535        11101111-10111111-10111111
     *
     * 0x10000     65536        11110000-10010000-10000000-10000000
     * 0x10A7B     68219        11110000-10010000-10101001-10111011
     * 0xE01EF     917999       11110011-10100000-10000111-10101111
     */

    using QChar = unsigned char;

    StringStream<QChar> stream;

    Unicode::ToUTF(0x0000, stream);
    EQ_VALUE(stream.Length(), 1, "stream.Length()");
    EQ_VALUE(*(stream.First()), 0, "stream.First()");
    stream.Clear();

    Unicode::ToUTF(0x003D, stream);
    EQ_VALUE(stream.Length(), 1, "stream.Length()");
    EQ_VALUE(*(stream.First()), '=', "stream.First()");
    stream.Clear();

    Unicode::ToUTF(0x007F, stream);
    EQ_VALUE(stream.Length(), 1, "stream.Length()");
    EQ_VALUE(*(stream.First()), QChar{127}, "stream.First()");
    stream.Clear();

    Unicode::ToUTF(0x0080, stream);
    EQ_VALUE(stream.Length(), 2, "stream.Length()");
    EQ_VALUE(*(stream.First()), QChar{194}, "stream.First()");
    EQ_VALUE(*(stream.First() + 1), QChar{128}, "*(stream.First()+1)");
    stream.Clear();

    Unicode::ToUTF(0x00A1, stream);
    EQ_VALUE(stream.Length(), 2, "stream.Length()");
    EQ_VALUE(*(stream.First()), QChar{194}, "stream.First()");
    EQ_VALUE(*(stream.First() + 1), QChar{161}, "*(stream.First()+1)");
    const auto *v00A1 = "¡";
    EQ_VALUE(stream, reinterpret_cast<const QChar *>(v00A1), "stream == v00A1");
    stream.Clear();

    Unicode::ToUTF(0x07FF, stream);
    EQ_VALUE(stream.Length(), 2, "stream.Length()");
    EQ_VALUE(*(stream.First()), QChar{223}, "stream.First()");
    EQ_VALUE(*(stream.First() + 1), QChar{191}, "*(stream.First()+1)");
    stream.Clear();

    Unicode::ToUTF(0x0800, stream);
    EQ_VALUE(stream.Length(), 3, "stream.Length()");
    EQ_VALUE(*(stream.First()), QChar{224}, "stream.First()");
    EQ_VALUE(*(stream.First() + 1), QChar{160}, "*(stream.First()+1)");
    EQ_VALUE(*(stream.First() + 2), QChar{128}, "*(stream.First() + 2)");
    stream.Clear();

    Unicode::ToUTF(0x08A7, stream);
    EQ_VALUE(stream.Length(), 3, "stream.Length()");
    EQ_VALUE(*(stream.First()), QChar{224}, "stream.First()");
    EQ_VALUE(*(stream.First() + 1), QChar{162}, "*(stream.First()+1)");
    EQ_VALUE(*(stream.First() + 2), QChar{167}, "*(stream.First() + 2)");
    const auto *v08A7 = "ࢧ";
    EQ_VALUE(stream, reinterpret_cast<const QChar *>(v08A7), "stream == v08A7");
    stream.Clear();

    Unicode::ToUTF(0xFFFF, stream);
    EQ_VALUE(stream.Length(), 3, "stream.Length()");
    EQ_VALUE(*(stream.First()), QChar{239}, "stream.First()");
    EQ_VALUE(*(stream.First() + 1), QChar{191}, "*(stream.First()+1)");
    EQ_VALUE(*(stream.First() + 2), QChar{191}, "*(stream.First() + 2)");
    stream.Clear();

    Unicode::ToUTF(0x10000, stream);
    EQ_VALUE(stream.Length(), 4, "stream.Length()");
    EQ_VALUE(*(stream.First()), QChar{240}, "stream.First()");
    EQ_VALUE(*(stream.First() + 1), QChar{144}, "*(stream.First()+1)");
    EQ_VALUE(*(stream.First() + 2), QChar{128}, "*(stream.First() + 2)");
    EQ_VALUE(*(stream.First() + 3), QChar{128}, "*(stream.First() + 3)");
    const auto *v10000 = "𐀀";
    EQ_VALUE(stream, reinterpret_cast<const QChar *>(v10000), "stream == v10000");
    stream.Clear();

    Unicode::ToUTF(0x10A7B, stream);
    EQ_VALUE(stream.Length(), 4, "stream.Length()");
    EQ_VALUE(*(stream.First()), QChar{240}, "stream.First()");
    EQ_VALUE(*(stream.First() + 1), QChar{144}, "*(stream.First()+1)");
    EQ_VALUE(*(stream.First() + 2), QChar{169}, "*(stream.First() + 2)");
    EQ_VALUE(*(stream.First() + 3), QChar{187}, "*(stream.First() + 3)");
    stream.Clear();

    Unicode::ToUTF(0xE01EF, stream);
    EQ_VALUE(stream.Length(), 4, "stream.Length()");
    EQ_VALUE(*(stream.First()), QChar{243}, "stream.First()");
    EQ_VALUE(*(stream.First() + 1), QChar{160}, "*(stream.First()+1)");
    EQ_VALUE(*(stream.First() + 2), QChar{135}, "*(stream.First() + 2)");
    EQ_VALUE(*(stream.First() + 3), QChar{175}, "*(stream.First() + 3)");
    stream.Clear();

    END_SUB_TEST;
}

static int TestToUTF16() {
    using QChar = char16_t;

    StringStream<QChar> stream;

    Unicode::ToUTF(0x0000, stream);
    EQ_VALUE(stream.Length(), 1, "stream.Length()");
    EQ_VALUE(*(stream.First()), 0, "stream.First()");
    stream.Clear();

    Unicode::ToUTF(0x003D, stream);
    EQ_VALUE(stream.Length(), 1, "stream.Length()");
    EQ_VALUE(*(stream.First()), u'=', "stream.First()");
    stream.Clear();

    Unicode::ToUTF(0x007F, stream);
    EQ_VALUE(stream.Length(), 1, "stream.Length()");
    EQ_VALUE(*(stream.First()), QChar{127}, "stream.First()");
    stream.Clear();

    Unicode::ToUTF(0x0080, stream);
    EQ_VALUE(stream.Length(), 1, "stream.Length()");
    EQ_VALUE(*(stream.First()), QChar{128}, "stream.First()");
    stream.Clear();

    Unicode::ToUTF(0x00A1, stream);
    EQ_VALUE(stream.Length(), 1, "stream.Length()");
    EQ_VALUE(*(stream.First()), QChar{161}, "stream.First()");
    stream.Clear();

    Unicode::ToUTF(0x07FF, stream);
    EQ_VALUE(stream.Length(), 1, "stream.Length()");
    EQ_VALUE(*(stream.First()), QChar{2047}, "stream.First()");
    stream.Clear();

    Unicode::ToUTF(0x0800, stream);
    EQ_VALUE(stream.Length(), 1, "stream.Length()");
    EQ_VALUE(*(stream.First()), QChar{2048}, "stream.First()");
    stream.Clear();

    Unicode::ToUTF(0x08A7, stream);
    EQ_VALUE(stream.Length(), 1, "stream.Length()");
    EQ_VALUE(*(stream.First()), QChar{2215}, "stream.First()");
    stream.Clear();

    Unicode::ToUTF(0xFFFF, stream);
    EQ_VALUE(stream.Length(), 1, "stream.Length()");
    EQ_VALUE(*(stream.First()), QChar{65535}, "stream.First()");
    stream.Clear();

    Unicode::ToUTF(0x10000, stream);
    EQ_VALUE(stream.Length(), 2, "stream.Length()");
    EQ_VALUE(*(stream.First()), QChar{55296}, "stream.First()");
    EQ_VALUE(*(stream.First() + 1), QChar{56320}, "*(stream.First()+1)");
    stream.Clear();

    Unicode::ToUTF(0x10A7B, stream);
    EQ_VALUE(stream.Length(), 2, "stream.Length()");
    EQ_VALUE(*(stream.First()), QChar{55298}, "stream.First()");
    EQ_VALUE(*(stream.First() + 1), QChar{56955}, "*(stream.First()+1)");
    stream.Clear();

    Unicode::ToUTF(0xE01EF, stream);
    EQ_VALUE(stream.Length(), 2, "stream.Length()");
    EQ_VALUE(*(stream.First()), QChar{56128}, "stream.First()");
    EQ_VALUE(*(stream.First() + 1), QChar{56815}, "*(stream.First()+1)");
    stream.Clear();

    END_SUB_TEST;
}

static int TestToUTF32() {
    StringStream<char32_t> stream;

    Unicode::ToUTF(0x0000, stream);
    EQ_VALUE(stream.Length(), 1, "stream.Length()");
    EQ_VALUE(*(stream.First()), 0, "stream.First()");
    stream.Clear();

    Unicode::ToUTF(0x003D, stream);
    EQ_VALUE(stream.Length(), 1, "stream.Length()");
    EQ_VALUE(*(stream.First()), U'=', "stream.First()");
    stream.Clear();

    Unicode::ToUTF(0x007F, stream);
    EQ_VALUE(stream.Length(), 1, "stream.Length()");
    EQ_VALUE(*(stream.First()), char32_t{127}, "stream.First()");
    stream.Clear();

    Unicode::ToUTF(0x0080, stream);
    EQ_VALUE(stream.Length(), 1, "stream.Length()");
    EQ_VALUE(*(stream.First()), char32_t{128}, "stream.First()");
    stream.Clear();

    Unicode::ToUTF(0x00A1, stream);
    EQ_VALUE(stream.Length(), 1, "stream.Length()");
    EQ_VALUE(*(stream.First()), char32_t{161}, "stream.First()");
    stream.Clear();

    Unicode::ToUTF(0x07FF, stream);
    EQ_VALUE(stream.Length(), 1, "stream.Length()");
    EQ_VALUE(*(stream.First()), char32_t{2047}, "stream.First()");
    stream.Clear();

    Unicode::ToUTF(0x0800, stream);
    EQ_VALUE(stream.Length(), 1, "stream.Length()");
    EQ_VALUE(*(stream.First()), char32_t{2048}, "stream.First()");
    stream.Clear();

    Unicode::ToUTF(0x08A7, stream);
    EQ_VALUE(stream.Length(), 1, "stream.Length()");
    EQ_VALUE(*(stream.First()), char32_t{2215}, "stream.First()");
    stream.Clear();

    Unicode::ToUTF(0xFFFF, stream);
    EQ_VALUE(stream.Length(), 1, "stream.Length()");
    EQ_VALUE(*(stream.First()), char32_t{65535}, "stream.First()");
    stream.Clear();

    Unicode::ToUTF(0x10000, stream);
    EQ_VALUE(stream.Length(), 1, "stream.Length()");
    EQ_VALUE(*(stream.First()), char32_t{65536}, "stream.First()");
    stream.Clear();

    Unicode::ToUTF(0x10A7B, stream);
    EQ_VALUE(stream.Length(), 1, "stream.Length()");
    EQ_VALUE(*(stream.First()), char32_t{68219}, "stream.First()");
    stream.Clear();

    Unicode::ToUTF(0xE01EF, stream);
    EQ_VALUE(stream.Length(), 1, "stream.Length()");
    EQ_VALUE(*(stream.First()), char32_t{917999}, "stream.First()");
    stream.Clear();

    END_SUB_TEST;
}

// static String<char> decToHex(SizeT code) {
//     StringStream<char> stream;
//     SizeT              hex = 0;

//     while (code != 0) {
//         hex  = code % 16U;
//         code = code / 16;
//         stream += char(hex + ((hex < 10) ? 48U : 55U));
//     }

//     String<char> str = stream.GetString();
//     char *       val = str.Storage();

//     if (str.Length() > 1) {
//         SizeT x = 0;
//         SizeT y = (str.Length() - 1);

//         // Reverse
//         do {
//             char tmp = val[x];
//             val[x]   = val[y];
//             val[y]   = tmp;
//             ++x;
//             --y;
//         } while (x < y);
//     }

//     return str;
// }

// static void convertTo4Hex(SizeT code) {
//     if (code < 0x10000U) {
//         std::cout << "\\u" << decToHex(code) << '\n';
//     } else {
//         code -= 0x10000U;
//         std::cout << "\n\\u" << decToHex(0xD800U | (code >> 10U)).First();
//         std::cout << "\\u" << decToHex(0xDC00U | (code & 0x3FFU)).First()
//                   << '\n';
//     }
// }

static int RunUnicodeTests() {
    // convertTo4Hex(0x10A7B);
    // convertTo4Hex(0x1F859);
    // convertTo4Hex(0x10283);

    STARTING_TEST("Unicode.hpp");

    START_TEST("ToUTF 8 Test", TestToUTF8);
    START_TEST("ToUTF 16 Test", TestToUTF16);
    START_TEST("ToUTF 32 Test", TestToUTF32);

    END_TEST("Unicode.hpp");
}

} // namespace Test
} // namespace Qentem

#endif
