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

#include "FixedArray.hpp"
#include "TestHelper.hpp"

#ifndef QENTEM_FIXEDARRAY_TESTS_H_
#define QENTEM_FIXEDARRAY_TESTS_H_

namespace Qentem {
namespace Test {

static int TestFixedArray() {
    FixedArray<unsigned int, 4>  arr1;
    FixedArray<unsigned int, 8>  arr2;
    FixedArray<unsigned int, 16> arr3;
    bool                         did_throw;

    EQ_VALUE(arr1.Size(), 0, "Size()");
    EQ_VALUE(arr2.Size(), 0, "Size()");
    EQ_VALUE(arr3.Size(), 0, "Size()");

    EQ_VALUE(arr1.Capacity(), 4, "Capacity()");
    EQ_VALUE(arr2.Capacity(), 8, "Capacity()");
    EQ_VALUE(arr3.Capacity(), 16, "Capacity()");

    EQ_TRUE(arr1.IsEmpty(), "IsEmpty()");
    EQ_TRUE(arr2.IsEmpty(), "IsEmpty()");
    EQ_TRUE(arr3.IsEmpty(), "IsEmpty()");

    EQ_FALSE(arr1.IsNotEmpty(), "IsNotEmpty()");
    EQ_FALSE(arr2.IsNotEmpty(), "IsNotEmpty()");
    EQ_FALSE(arr3.IsNotEmpty(), "IsNotEmpty()");

    EQ_FALSE(arr1.IsFull(), "IsFull()");
    EQ_FALSE(arr2.IsFull(), "IsFull()");
    EQ_FALSE(arr3.IsFull(), "IsFull()");

    EQ_VALUE(arr1.First(), arr1.End(), "First()");
    EQ_VALUE(arr2.First(), arr2.End(), "First()");
    EQ_VALUE(arr3.First(), arr3.End(), "First()");

    for (unsigned int i = 0; i < arr1.Capacity(); i++) {
        arr1 += i;
    }

    for (unsigned int i = 0; i < arr2.Capacity(); i++) {
        arr2 += i;
    }

    for (unsigned int i = 0; i < arr3.Capacity(); i++) {
        arr3 += i;
    }

    EQ_VALUE(arr1.Size(), arr1.Capacity(), "Size()");
    EQ_VALUE(arr2.Size(), arr2.Capacity(), "Size()");
    EQ_VALUE(arr3.Size(), arr3.Capacity(), "Size()");

    EQ_FALSE(arr1.IsEmpty(), "IsEmpty()");
    EQ_FALSE(arr2.IsEmpty(), "IsEmpty()");
    EQ_FALSE(arr3.IsEmpty(), "IsEmpty()");

    EQ_TRUE(arr1.IsNotEmpty(), "IsNotEmpty()");
    EQ_TRUE(arr2.IsNotEmpty(), "IsNotEmpty()");
    EQ_TRUE(arr3.IsNotEmpty(), "IsNotEmpty()");

    EQ_TRUE(arr1.IsFull(), "IsFull()");
    EQ_TRUE(arr2.IsFull(), "IsFull()");
    EQ_TRUE(arr3.IsFull(), "IsFull()");

    NOT_EQ_VALUE(arr1.First(), arr1.End(), "First()");
    NOT_EQ_VALUE(arr2.First(), arr2.End(), "First()");
    NOT_EQ_VALUE(arr3.First(), arr3.End(), "First()");

    try {
        did_throw = false;
        arr1 += 5U;
    } catch (...) {
        did_throw = true;
    }

    EQ_TRUE(did_throw, "did_throw");

    try {
        did_throw = false;
        arr2 += 5U;
    } catch (...) {
        did_throw = true;
    }

    EQ_TRUE(did_throw, "did_throw");

    try {
        did_throw = false;
        arr3 += 5U;
    } catch (...) {
        did_throw = true;
    }

    EQ_TRUE(did_throw, "did_throw");

    try {
        did_throw = false;
        arr3 += static_cast<unsigned int &&>(5U);
    } catch (...) {
        did_throw = true;
    }

    EQ_TRUE(did_throw, "did_throw");

    unsigned int uii = 5;

    try {
        did_throw = false;
        arr3 += static_cast<unsigned int &>(uii);
    } catch (...) {
        did_throw = true;
    }

    EQ_TRUE(did_throw, "did_throw");

    arr1.Clear();
    arr2.Clear();
    arr3.Clear();

    EQ_VALUE(arr1.Size(), 0, "Size()");
    EQ_VALUE(arr2.Size(), 0, "Size()");
    EQ_VALUE(arr3.Size(), 0, "Size()");

    EQ_TRUE(arr1.IsEmpty(), "IsEmpty()");
    EQ_TRUE(arr2.IsEmpty(), "IsEmpty()");
    EQ_TRUE(arr3.IsEmpty(), "IsEmpty()");

    EQ_FALSE(arr1.IsNotEmpty(), "IsNotEmpty()");
    EQ_FALSE(arr2.IsNotEmpty(), "IsNotEmpty()");
    EQ_FALSE(arr3.IsNotEmpty(), "IsNotEmpty()");

    EQ_FALSE(arr1.IsFull(), "IsFull()");
    EQ_FALSE(arr2.IsFull(), "IsFull()");
    EQ_FALSE(arr3.IsFull(), "IsFull()");

    arr1 += 5U;
    arr2 += 5U;
    arr3 += 5U;

    EQ_VALUE(arr1.Size(), 1, "Size()");
    EQ_VALUE(arr2.Size(), 1, "Size()");
    EQ_VALUE(arr3.Size(), 1, "Size()");

    EQ_FALSE(arr1.IsEmpty(), "IsEmpty()");
    EQ_FALSE(arr2.IsEmpty(), "IsEmpty()");
    EQ_FALSE(arr3.IsEmpty(), "IsEmpty()");

    EQ_TRUE(arr1.IsNotEmpty(), "IsNotEmpty()");
    EQ_TRUE(arr2.IsNotEmpty(), "IsNotEmpty()");
    EQ_TRUE(arr3.IsNotEmpty(), "IsNotEmpty()");

    EQ_FALSE(arr1.IsFull(), "IsFull()");
    EQ_FALSE(arr2.IsFull(), "IsFull()");
    EQ_FALSE(arr3.IsFull(), "IsFull()");

    EQ_VALUE(*(arr1.First()), 5U, "First()");

    arr1 += 10U;
    arr1 += 100U;

    EQ_VALUE(arr1.End(), (arr1.First() + arr1.Size()), "End()");

    arr1.Clear();

    arr1.SetSize(10000);
    EQ_VALUE(arr1.Size(), 0, "Size()");
    arr1.SetSize(arr1.Capacity());
    EQ_VALUE(arr1.Size(), arr1.Capacity(), "Size()");

    END_SUB_TEST;
}

static int RunFixedArrayTests() {
    STARTING_TEST("FixedArray.hpp");

    START_TEST("FixedArray Test", TestFixedArray);

    END_TEST("FixedArray.hpp");
}

} // namespace Test
} // namespace Qentem

#endif
