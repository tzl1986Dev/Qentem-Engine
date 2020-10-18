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

#ifndef QENTEM_ARRAY_H_
#define QENTEM_ARRAY_H_

namespace Qentem {

/*
 * Simple resizable array, with pointer taging.
 */
template <typename Type_>
class Array {
  public:
    Array() = default;

    explicit Array(SizeT size) : capacity_(size) {
        if (size != 0) {
            allocate();
        }
    }

    Array(Array &&arr) noexcept
        : index_(arr.Size()), capacity_(arr.Capacity()) {
#ifdef QENTEM_POINTER_TAGGING
        storage_.ptr_ = arr.Storage();
#else
        storage_ = arr.Storage();
#endif
        arr.clearStorage();
        arr.setSize(0);
        arr.setCapacity(0);
    }

    Array(const Array &arr) : capacity_(arr.Size()) {
        if (Capacity() != 0) {
            allocate();

            Type_ *des = Storage();
            Type_ *src = arr.Storage();

            do {
                Memory::Construct((des + Size()), src[Size()]);
                ++index_;
            } while (Size() != Capacity());
        }
    }

    ~Array() {
        Type_ *current = Storage();

        if (current != nullptr) {
            Memory::Destruct(current, End());
            deallocate(current);
        }
    }

    Type_ &operator[](SizeT index) const {
        if (index < Size()) {
            return Storage()[index];
        }

        throw 1; // Index out of range
    }

    Array &operator=(Array &&arr) noexcept {
        if (this != &arr) {
            Type_ *current = Storage();

            if (current != nullptr) {
                Memory::Destruct(current, End());
                deallocate(current);
            }

            setStorage(arr.Storage());
            setSize(arr.Size());
            setCapacity(arr.Capacity());

            arr.clearStorage();
            arr.setSize(0);
            arr.setCapacity(0);
        }

        return *this;
    }

    Array &operator=(const Array &arr) {
        if (this != &arr) {
            Reserve(arr.Size());

            Type_ *des = Storage();
            Type_ *src = arr.Storage();

            while (Size() != Capacity()) {
                Memory::Construct((des + Size()), src[Size()]);
                ++index_;
            }
        }

        return *this;
    }

    void operator+=(Array &&arr) {
        if (Capacity() == 0) {
            // If the array hasn't allocated any memory, then there is no need
            // for rest.
            setStorage(arr.Storage());
            setSize(arr.Size());
            setCapacity(arr.Capacity());
        } else {
            const SizeT n_size = (Size() + arr.Size());

            if (n_size > Capacity()) {
                resize(n_size);
            }

            if (arr.IsNotEmpty()) {
                Memory::Copy((Storage() + Size()), arr.First(),
                             arr.Size() * sizeof(Type_));
            }

            setSize(n_size);
            arr.deallocate(arr.Storage());
        }

        arr.clearStorage();
        arr.setSize(0);
        arr.setCapacity(0);
    }

    void operator+=(const Array &arr) { copyArray(arr); }

    void operator+=(Type_ &&item) {
        if (Size() == Capacity()) {
            if (Capacity() == 0) {
                setCapacity(1);
            }

            resize(Capacity() << 1U);
        }

        Memory::Construct((Storage() + Size()), static_cast<Type_ &&>(item));
        ++index_;
    }

    inline void operator+=(const Type_ &item) {
        *this += static_cast<Type_ &&>(Type_(item));
    }

    inline Array &Insert(Array &&arr) {
        *this += static_cast<Array &&>(arr);
        return *this;
    }

    inline Array &Insert(const Array &arr) {
        copyArray(arr);
        return *this;
    }

    inline Array &Insert(Type_ &&item) {
        *this += static_cast<Type_ &&>(item);
        return *this;
    }

    inline Array &Insert(const Type_ &item) {
        *this += static_cast<Type_ &&>(Type_(item));
        return *this;
    }

    void Reset() noexcept {
        Type_ *current = Storage();

        if (current != nullptr) {
            Memory::Destruct(current, End());
            deallocate(current);

            clearStorage();
            setSize(0);
            setCapacity(0);
        }
    }

    void Clear() noexcept {
        Memory::Destruct(Storage(), End());
        setSize(0);
    }

    Type_ *Eject() noexcept {
        Type_ *tmp = Storage();
        clearStorage();
        setSize(0);
        setCapacity(0);

        return tmp;
    }

    void Reserve(SizeT size) {
        Reset();

        if (size != 0) {
            setCapacity(size);
            allocate();
        }
    }

    void Resize(SizeT new_size) {
        if (new_size == 0) {
            Reset();
            return;
        }

        if (Size() > new_size) {
            // Shrink
            Memory::Destruct((Storage() + new_size), End());
            setSize(new_size);
        }

        resize(new_size);
    }

    inline void Expect(SizeT size) {
        const SizeT n_size = (size + Size());

        if (n_size > Capacity()) {
            resize(n_size);
        }
    }

    void Compress() {
        // Remove excess storage;
        if (Size() != Capacity()) {
            Resize(Size());
        }
    }

    void GoBackTo(SizeT index) noexcept {
        if (index < Size()) {
            Memory::Destruct((Storage() + index), End());
            setSize(index);
        }
    }

    void ResizeAndInitialize(SizeT new_size) {
        Resize(new_size);

        if (new_size > Size()) {
            Type_ *current = Storage();
            Memory::Construct((current + Size()), (current + new_size),
                              Type_());
        }

        setSize(Capacity());
    }

#ifdef QENTEM_POINTER_TAGGING
    inline Type_ *Storage() const noexcept {
        return reinterpret_cast<Type_ *>(storage_.int_ & 0xFFFFFFFFFFFFULL);
    }
#else
    inline Type_ *Storage() const noexcept { return storage_; }
#endif

    inline SizeT        Size() const noexcept { return index_; }
    inline SizeT        Capacity() const noexcept { return capacity_; }
    inline const Type_ *First() const noexcept { return Storage(); }
    inline const Type_ *End() const noexcept { return (First() + Size()); }
    inline bool         IsEmpty() const noexcept { return (Size() == 0); }
    inline bool         IsNotEmpty() const noexcept { return !(IsEmpty()); }

    inline const Type_ *Last() const noexcept {
        if (IsNotEmpty()) {
            return (Storage() + (Size() - 1));
        }

        return nullptr;
    }

    //////////// Private ////////////

  private:
    void setStorage(Type_ *new_storage) noexcept {
#ifdef QENTEM_POINTER_TAGGING
        storage_.int_ &= 0xFFFF000000000000ULL; // Preserve the tag
        storage_.int_ |= reinterpret_cast<unsigned long long>(
            new_storage); // Restore the tag
#else
        storage_ = new_storage;
#endif
    }

    void allocate() { setStorage(Memory::Allocate<Type_>(Capacity())); }
    void deallocate(Type_ *old_storage) { Memory::Deallocate(old_storage); }
    void clearStorage() noexcept { setStorage(nullptr); }
    void setSize(SizeT new_size) noexcept { index_ = new_size; }
    void setCapacity(SizeT new_capacity) noexcept { capacity_ = new_capacity; }

    void resize(SizeT new_size) {
        Type_ *old = Storage();
        setCapacity(new_size);
        allocate();

        if (IsNotEmpty()) {
            Memory::Copy(Storage(), old, (Size() * sizeof(Type_)));
        }

        deallocate(old);
    }

    QENTEM_NOINLINE void copyArray(const Array &arr) {
        const SizeT n_size = (Size() + arr.Size());

        if (n_size > Capacity()) {
            resize(n_size);
        }

        Type_ *des = Storage();
        Type_ *src = arr.Storage();
        SizeT  n   = 0;

        while (n != arr.Size()) {
            Memory::Construct((des + Size()), src[n]);
            ++index_;
            ++n;
        }
    }

#ifdef QENTEM_POINTER_TAGGING
    union {
        unsigned long long int_;
        Type_ *            ptr_;
    } storage_{0};
#else
    Type_ *storage_{nullptr};
#endif

    SizeT index_{0};
    SizeT capacity_{0};
};

} // namespace Qentem

#endif
