/*
 * Copyright (c) 2023 Hani Ammar
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

#include "QTest.hpp"
#include "Array.hpp"
#include "String.hpp"

#ifndef QENTEM_ARRAY_TESTS_H
#define QENTEM_ARRAY_TESTS_H

namespace Qentem {
namespace Test {

static void TestArray1(QTest &helper) {
    const SizeT *storage;
    Array<SizeT> numbers1;
    Array<SizeT> numbers2(8);

    helper.IsEqual(numbers1.Size(), 0U, __LINE__);
    helper.IsTrue(numbers1.IsEmpty(), __LINE__);
    helper.IsFalse(numbers1.IsNotEmpty(), __LINE__);
    helper.IsEqual(numbers1.Capacity(), 0U, __LINE__);
    helper.IsNull(numbers1.First(), __LINE__);
    helper.IsNull(numbers1.Last(), __LINE__);

    helper.IsEqual(numbers2.Size(), 0U, __LINE__);
    helper.IsEqual(numbers2.Capacity(), 8U, __LINE__);
    helper.IsNotNull(numbers2.First(), __LINE__);

    numbers2.Reset();
    helper.IsEqual(numbers2.Size(), 0U, __LINE__);
    helper.IsEqual(numbers2.Capacity(), 0U, __LINE__);
    helper.IsNull(numbers2.First(), __LINE__);

    numbers1.Reserve(5);
    helper.IsEqual(numbers1.Size(), 0U, __LINE__);
    helper.IsEqual(numbers1.Capacity(), 5U, __LINE__);
    helper.IsNotNull(numbers1.First(), __LINE__);

    numbers1.Reserve(10);
    helper.IsEqual(numbers1.Size(), 0U, __LINE__);
    helper.IsEqual(numbers1.Capacity(), 10U, __LINE__);
    helper.IsNotNull(numbers1.First(), __LINE__);

    numbers1.Resize(18);
    helper.IsEqual(numbers1.Size(), 0U, __LINE__);
    helper.IsEqual(numbers1.Capacity(), 18U, __LINE__);
    helper.IsNotNull(numbers1.First(), __LINE__);

    storage = numbers1.First();
    numbers1.Resize(4);
    helper.IsEqual(numbers1.Size(), 0U, __LINE__);
    helper.IsEqual(numbers1.Capacity(), 4U, __LINE__);
    helper.IsNotNull(numbers1.First(), __LINE__);
    helper.IsNotEqual(numbers1.First(), storage, __LINE__);

    numbers2.Resize(5);
    helper.IsEqual(numbers2.Size(), 0U, __LINE__);
    helper.IsEqual(numbers2.Capacity(), 5U, __LINE__);
    helper.IsNotNull(numbers2.First(), __LINE__);

    numbers2.Resize(2);
    helper.IsEqual(numbers2.Size(), 0U, __LINE__);
    helper.IsEqual(numbers2.Capacity(), 2U, __LINE__);
    helper.IsNotNull(numbers2.First(), __LINE__);

    numbers2.Resize(0);
    helper.IsEqual(numbers2.Size(), 0U, __LINE__);
    helper.IsEqual(numbers2.Capacity(), 0U, __LINE__);
    helper.IsNull(numbers2.First(), __LINE__);

    numbers1.Reserve(0);
    helper.IsEqual(numbers1.Size(), 0U, __LINE__);
    helper.IsEqual(numbers1.Capacity(), 0U, __LINE__);
    helper.IsNull(numbers1.First(), __LINE__);

    numbers1.Reset();
    numbers2.Reset();

    numbers1.ResizeAndInitialize(8);
    storage = numbers1.First();
    helper.IsEqual(numbers1.Size(), 8U, __LINE__);
    helper.IsFalse(numbers1.IsEmpty(), __LINE__);
    helper.IsTrue(numbers1.IsNotEmpty(), __LINE__);
    helper.IsEqual(numbers1.Capacity(), 8U, __LINE__);
    helper.IsNotNull(numbers1.First(), __LINE__);

    numbers1.ResizeAndInitialize(4);
    helper.IsNotEqual(numbers1.First(), storage, __LINE__);

    storage  = numbers1.First();
    numbers2 = numbers1;
    helper.IsEqual(numbers1.Size(), 4U, __LINE__);
    helper.IsEqual(numbers1.Capacity(), 4U, __LINE__);
    helper.IsNotNull(numbers1.First(), __LINE__);
    helper.IsEqual(numbers2.Size(), 4U, __LINE__);
    helper.IsEqual(numbers2.Capacity(), 4U, __LINE__);
    helper.IsNotNull(numbers2.First(), __LINE__);
    helper.IsNotEqual(numbers2.First(), storage, __LINE__);

    numbers1.ResizeAndInitialize(16);
    helper.IsEqual(numbers1.Size(), 16U, __LINE__);
    helper.IsEqual(numbers1.Capacity(), 16U, __LINE__);
    helper.IsNotNull(numbers1.First(), __LINE__);

    storage  = numbers1.First();
    numbers2 = numbers1;
    helper.IsEqual(numbers2.Size(), 16U, __LINE__);
    helper.IsEqual(numbers2.Capacity(), 16U, __LINE__);
    helper.IsNotNull(numbers2.First(), __LINE__);
    helper.IsNotEqual(numbers2.First(), storage, __LINE__);

    numbers2 = Memory::Move(numbers1);
    helper.IsEqual(numbers2.Size(), 16U, __LINE__);
    helper.IsEqual(numbers2.Capacity(), 16U, __LINE__);
    helper.IsEqual(numbers2.First(), storage, __LINE__);

    helper.IsNull(numbers1.Storage(), __LINE__);
    helper.IsEqual(numbers1.Size(), 0U, __LINE__);
    helper.IsEqual(numbers1.Capacity(), 0U, __LINE__);
    helper.IsNull(numbers1.First(), __LINE__);

    storage  = numbers1.First();
    numbers1 = Array<SizeT>(numbers2);
    helper.IsEqual(numbers1.Size(), 16U, __LINE__);
    helper.IsEqual(numbers1.Capacity(), 16U, __LINE__);
    helper.IsNotNull(numbers1.First(), __LINE__);
    helper.IsNotEqual(numbers1.First(), storage, __LINE__);

    storage  = numbers2.First();
    numbers1 = Array<SizeT>(Memory::Move(numbers2));
    helper.IsEqual(numbers1.Size(), 16U, __LINE__);
    helper.IsEqual(numbers1.Capacity(), 16U, __LINE__);
    helper.IsNotNull(numbers1.First(), __LINE__);
    helper.IsEqual(numbers1.First(), storage, __LINE__);
    helper.IsNull(numbers2.Storage(), __LINE__);
    helper.IsEqual(numbers2.Size(), 0U, __LINE__);
    helper.IsEqual(numbers2.Capacity(), 0U, __LINE__);
    helper.IsNull(numbers2.First(), __LINE__);

    storage = numbers1.First();
    numbers1.Clear();
    helper.IsEqual(numbers1.Size(), 0U, __LINE__);
    helper.IsEqual(numbers1.Capacity(), 16U, __LINE__);
    helper.IsNotNull(numbers1.First(), __LINE__);
    helper.IsEqual(numbers1.First(), storage, __LINE__);

    numbers1.ResizeAndInitialize(3);
    numbers2.ResizeAndInitialize(5);
    storage = numbers2.First();

    numbers1 += numbers2;
    helper.IsEqual(numbers1.Size(), 8U, __LINE__);
    helper.IsEqual(numbers1.Capacity(), 8U, __LINE__);
    helper.IsNotNull(numbers1.First(), __LINE__);
    helper.IsNotEqual(numbers1.First(), storage, __LINE__);

    storage = numbers1.First();
    numbers1 += Memory::Move(numbers2);
    helper.IsEqual(numbers1.Size(), 13U, __LINE__);
    helper.IsEqual(numbers1.Capacity(), 13U, __LINE__);
    helper.IsNotNull(numbers1.First(), __LINE__);
    helper.IsNotEqual(numbers1.First(), storage, __LINE__);
    helper.IsEqual(numbers2.Size(), 0U, __LINE__);
    helper.IsEqual(numbers2.Capacity(), 0U, __LINE__);
    helper.IsNull(numbers2.First(), __LINE__);

    numbers2.ResizeAndInitialize(5);
    numbers1.Resize(18);
    storage = numbers1.First();
    numbers1 += Memory::Move(numbers2);
    helper.IsEqual(numbers1.Size(), 18U, __LINE__);
    helper.IsEqual(numbers1.Capacity(), 18U, __LINE__);
    helper.IsNotNull(numbers1.First(), __LINE__);
    helper.IsEqual(numbers1.First(), storage, __LINE__);

    storage = numbers1.First();
    numbers2 += Memory::Move(numbers1);
    helper.IsEqual(numbers2.Size(), 18U, __LINE__);
    helper.IsEqual(numbers2.Capacity(), 18U, __LINE__);
    helper.IsNotNull(numbers2.First(), __LINE__);
    helper.IsEqual(numbers2.First(), storage, __LINE__);

    SizeT *tmp = numbers2.Detach();
    helper.IsEqual(numbers2.Size(), 0U, __LINE__);
    helper.IsEqual(numbers2.Capacity(), 0U, __LINE__);
    helper.IsNull(numbers2.First(), __LINE__);
    helper.IsEqual(tmp, storage, __LINE__);

    Memory::Deallocate(tmp);
}

static void TestArray2(QTest &helper) {
    const SizeT *storage;
    Array<SizeT> numbers1;
    Array<SizeT> numbers2;

    numbers2.Reserve(4);
    numbers1.ResizeAndInitialize(4);
    storage = numbers2.First();
    numbers2.Insert(numbers1);
    helper.IsEqual(numbers2.Size(), 4U, __LINE__);
    helper.IsEqual(numbers2.Capacity(), 4U, __LINE__);
    helper.IsNotNull(numbers2.First(), __LINE__);
    helper.IsEqual(numbers2.First(), storage, __LINE__);
    helper.IsEqual(numbers2.Last(), (storage + 3), __LINE__);
    helper.IsNotNull(numbers1.Last(), __LINE__);

    numbers1.Reserve(10);
    numbers2.ResizeAndInitialize(4);
    numbers2.Insert(numbers1);
    helper.IsEqual(numbers2.Size(), 4U, __LINE__);
    helper.IsEqual(numbers2.Capacity(), 4U, __LINE__);
    helper.IsNotNull(numbers2.First(), __LINE__);

    numbers1.ResizeAndInitialize(4);
    numbers2.Insert(numbers1);
    helper.IsEqual(numbers2.Size(), 8U, __LINE__);
    helper.IsEqual(numbers2.Capacity(), 8U, __LINE__);
    helper.IsNotNull(numbers2.First(), __LINE__);

    storage = numbers1.First();
    numbers2.Insert(Memory::Move(numbers1));
    helper.IsEqual(numbers2.Size(), 12U, __LINE__);
    helper.IsEqual(numbers2.Capacity(), 12U, __LINE__);
    helper.IsNotNull(numbers2.First(), __LINE__);
    helper.IsNotEqual(numbers2.First(), storage, __LINE__);
}

static void TestArray3(QTest &helper) {
    Array<SizeT>        numbers1;
    Array<SizeT>        numbers2(8);
    Array<String<char>> strings;

    for (SizeT i = 0; i < 8; i++) {
        numbers1 += i;
    }

    const SizeT *storage1 = numbers1.Storage();
    const SizeT *storage2 = numbers1.Storage();

    helper.IsEqual(numbers1.Size(), 8U, __LINE__);
    helper.IsTrue((numbers1.Capacity() >= 8U), __LINE__);
    helper.IsNotNull(numbers1.First(), __LINE__);

    SizeT sum = 0;
    for (const SizeT &num : numbers1) {
        sum += num;
    }

    helper.IsEqual(sum, 28U, __LINE__);

    numbers2.Insert(storage1[0]);
    numbers2.Insert(storage1[1]);

    for (SizeT i = 2; i < 8; i++) {
        numbers2.Insert(storage1[i]);
        helper.IsEqual(storage2[i], storage1[i], __LINE__);
    }

    helper.IsEqual(numbers2.Size(), 8U, __LINE__);
    helper.IsEqual(numbers2.Capacity(), 8U, __LINE__);

    numbers2.Resize(16);
    helper.IsEqual(numbers2.Size(), 8U, __LINE__);
    helper.IsEqual(numbers2.Capacity(), 16U, __LINE__);

    numbers2.Compress();
    helper.IsEqual(numbers2.Size(), 8U, __LINE__);
    helper.IsEqual(numbers2.Capacity(), 8U, __LINE__);

    storage2 = numbers2.Storage();
    numbers2.Clear();
    helper.IsEqual(numbers2.Size(), 0U, __LINE__);
    helper.IsEqual(numbers2.Capacity(), 8U, __LINE__);
    helper.IsEqual(numbers2.Storage(), storage2, __LINE__);

    numbers2.Reset();
    helper.IsEqual(numbers2.Size(), 0U, __LINE__);
    helper.IsEqual(numbers2.Capacity(), 0U, __LINE__);

    // Checking move
    String<char> str1("val--------------------------------1");
    String<char> str2("val--------------------------------2");

    const char *str1_cstr = str1.First();
    const char *str2_cstr = str2.First();

    strings += Memory::Move(str1);

    helper.IsEqual(strings.Storage()[0].First(), str1_cstr, __LINE__);

    strings.Insert(Memory::Move(str2));
    helper.IsEqual(strings.Storage()[1].First(), str2_cstr, __LINE__);

    strings += str1;
    helper.IsNotEqual(strings.Storage()[2].First(), str1_cstr, __LINE__);

    strings.Insert(str2);
    helper.IsNotEqual(strings.Storage()[3].First(), str2_cstr, __LINE__);

    // Checking move after expanding.
    for (SizeT i = 0; i < 16; i++) {
        strings += String<char>("");
    }

    helper.IsEqual(strings.Storage()[0].First(), str1_cstr, __LINE__);
    helper.IsEqual(strings.Storage()[1].First(), str2_cstr, __LINE__);

    ///////////////////////////
    numbers1.Clear();

    SizeT &nu1 = numbers1.Insert(5);
    ++nu1;

    helper.IsEqual(*(numbers1.First()), SizeT{6}, __LINE__);

    /////////////////////
    numbers1.Clear();
    numbers1 += 1;

    for (SizeT &num : numbers1) {
        num += 10;
    }

    helper.IsEqual(*(numbers1.First()), SizeT{11}, __LINE__);
    /////////////////////
    const Array<SizeT> numbers_init{8U, true};
    helper.IsEqual(numbers_init.Size(), 8U, __LINE__);

    /////////////////////

    numbers1.Clear();
    numbers1 += 6;
    numbers1 += 7;
    numbers1 += 5;
    numbers1 += 1;
    numbers1 += 3;
    numbers1 += 4;
    numbers1 += 2;

    SizeT *storage = numbers1.Storage();
    numbers1.Swap(storage[3], storage[6]);
    numbers1.Swap(storage[0], storage[6]);
    numbers1.Swap(storage[3], storage[1]);
    numbers1.Swap(storage[2], storage[4]);
    numbers1.Swap(storage[3], storage[5]);
    numbers1.Swap(storage[6], storage[5]);

    helper.IsEqual(storage[0], 1U, __LINE__);
    helper.IsEqual(storage[1], 2U, __LINE__);
    helper.IsEqual(storage[2], 3U, __LINE__);
    helper.IsEqual(storage[3], 4U, __LINE__);
    helper.IsEqual(storage[4], 5U, __LINE__);
    helper.IsEqual(storage[5], 6U, __LINE__);
    helper.IsEqual(storage[6], 7U, __LINE__);
}

static void TestArray4(QTest &helper) {
    Array<String<char>> strings1;
    Array<String<char>> strings2;

    String<char> str1("val--------------------------------1");
    String<char> str2("val--------------------------------2");

    const char *str1_cstr = str1.First();
    const char *str2_cstr = str2.First();

    strings1 += Memory::Move(str1);
    strings1 += Memory::Move(str2);

    strings2 += strings1;
    String<char> *storage2 = strings2.Storage();

    helper.IsEqual(strings2.Size(), 2U, __LINE__);
    helper.IsNotNull(strings2.First(), __LINE__);
    helper.IsNotEqual(storage2[0].First(), str1_cstr, __LINE__);
    helper.IsNotEqual(storage2[1].First(), str2_cstr, __LINE__);

    strings2.Reserve(2);
    strings2 += Memory::Move(strings1);
    storage2 = strings2.Storage();

    helper.IsEqual(strings2.Size(), 2U, __LINE__);
    helper.IsNotNull(strings2.First(), __LINE__);
    helper.IsEqual(storage2[0].First(), str1_cstr, __LINE__);
    helper.IsEqual(storage2[1].First(), str2_cstr, __LINE__);

    strings2.Reset();

    strings2.Expect(0);
    helper.IsEqual(strings2.Capacity(), 0U, __LINE__);

    strings2.Expect(1);
    helper.IsEqual(strings2.Capacity(), 1U, __LINE__);

    strings2.Expect(2);
    helper.IsEqual(strings2.Capacity(), 2U, __LINE__);

    strings2.Expect(3);
    helper.IsEqual(strings2.Capacity(), 4U, __LINE__);

    strings2.Expect(4);
    helper.IsEqual(strings2.Capacity(), 4U, __LINE__);

    strings2.Expect(5);
    helper.IsEqual(strings2.Capacity(), 8U, __LINE__);

    strings2.Expect(10);
    helper.IsEqual(strings2.Capacity(), 16U, __LINE__);

    strings2.Expect(11);
    helper.IsEqual(strings2.Capacity(), 16U, __LINE__);
}

static void TestArraySort(QTest &helper) {
    Array<SizeT32> numbers;

    numbers += 3;
    numbers += 0;
    numbers += 5;
    numbers += 1;
    numbers += 4;
    numbers += 2;

    numbers.Sort();

    SizeT32 *storage = numbers.Storage();

    helper.IsEqual(storage[0], 0U, __LINE__);
    helper.IsEqual(storage[1], 1U, __LINE__);
    helper.IsEqual(storage[2], 2U, __LINE__);
    helper.IsEqual(storage[3], 3U, __LINE__);
    helper.IsEqual(storage[4], 4U, __LINE__);
    helper.IsEqual(storage[5], 5U, __LINE__);

    numbers.Sort(false);
    storage = numbers.Storage();

    helper.IsEqual(storage[0], 5U, __LINE__);
    helper.IsEqual(storage[1], 4U, __LINE__);
    helper.IsEqual(storage[2], 3U, __LINE__);
    helper.IsEqual(storage[3], 2U, __LINE__);
    helper.IsEqual(storage[4], 1U, __LINE__);
    helper.IsEqual(storage[5], 0U, __LINE__);

    numbers.Reset();

    numbers += 3;
    numbers += 0;
    numbers += 5;
    numbers += 1;
    numbers += 4;
    numbers += 2;

    numbers.Sort(false);
    storage = numbers.Storage();

    helper.IsEqual(storage[0], 5U, __LINE__);
    helper.IsEqual(storage[1], 4U, __LINE__);
    helper.IsEqual(storage[2], 3U, __LINE__);
    helper.IsEqual(storage[3], 2U, __LINE__);
    helper.IsEqual(storage[4], 1U, __LINE__);
    helper.IsEqual(storage[5], 0U, __LINE__);

    numbers.Reset();

    numbers += 0;
    numbers += 1;
    numbers += 2;
    numbers += 3;
    numbers += 4;
    numbers += 5;

    numbers.Sort();
    storage = numbers.Storage();

    helper.IsEqual(storage[0], 0U, __LINE__);
    helper.IsEqual(storage[1], 1U, __LINE__);
    helper.IsEqual(storage[2], 2U, __LINE__);
    helper.IsEqual(storage[3], 3U, __LINE__);
    helper.IsEqual(storage[4], 4U, __LINE__);
    helper.IsEqual(storage[5], 5U, __LINE__);

    numbers.Sort(false);
    storage = numbers.Storage();

    helper.IsEqual(storage[0], 5U, __LINE__);
    helper.IsEqual(storage[1], 4U, __LINE__);
    helper.IsEqual(storage[2], 3U, __LINE__);
    helper.IsEqual(storage[3], 2U, __LINE__);
    helper.IsEqual(storage[4], 1U, __LINE__);
    helper.IsEqual(storage[5], 0U, __LINE__);

    Array<String<char>> strings;

    strings += String<char>("2017");
    strings += String<char>("2020");
    strings += String<char>("2019");
    strings += String<char>("2018");
    strings += String<char>("2021");
    strings += String<char>("2018");
    strings += String<char>("2021");

    strings.Sort();
    String<char> *storage_str = strings.Storage();

    helper.IsEqual(storage_str[0], "2017", __LINE__);
    helper.IsEqual(storage_str[1], "2018", __LINE__);
    helper.IsEqual(storage_str[2], "2018", __LINE__);
    helper.IsEqual(storage_str[3], "2019", __LINE__);
    helper.IsEqual(storage_str[4], "2020", __LINE__);
    helper.IsEqual(storage_str[5], "2021", __LINE__);
    helper.IsEqual(storage_str[6], "2021", __LINE__);

    strings.Sort(false);
    storage_str = strings.Storage();

    helper.IsEqual(storage_str[0], "2021", __LINE__);
    helper.IsEqual(storage_str[1], "2021", __LINE__);
    helper.IsEqual(storage_str[2], "2020", __LINE__);
    helper.IsEqual(storage_str[3], "2019", __LINE__);
    helper.IsEqual(storage_str[4], "2018", __LINE__);
    helper.IsEqual(storage_str[5], "2018", __LINE__);
    helper.IsEqual(storage_str[6], "2017", __LINE__);

    strings.Reset();

    strings += String<char>("2020");
    strings += String<char>("2017");
    strings += String<char>("2019");
    strings += String<char>("2018");
    strings += String<char>("2021");
    strings += String<char>("2021");
    strings += String<char>("2018");

    strings.Sort();
    storage_str = strings.Storage();

    helper.IsEqual(storage_str[0], "2017", __LINE__);
    helper.IsEqual(storage_str[1], "2018", __LINE__);
    helper.IsEqual(storage_str[2], "2018", __LINE__);
    helper.IsEqual(storage_str[3], "2019", __LINE__);
    helper.IsEqual(storage_str[4], "2020", __LINE__);
    helper.IsEqual(storage_str[5], "2021", __LINE__);
    helper.IsEqual(storage_str[6], "2021", __LINE__);

    strings.Sort(false);
    storage_str = strings.Storage();

    helper.IsEqual(storage_str[0], "2021", __LINE__);
    helper.IsEqual(storage_str[1], "2021", __LINE__);
    helper.IsEqual(storage_str[2], "2020", __LINE__);
    helper.IsEqual(storage_str[3], "2019", __LINE__);
    helper.IsEqual(storage_str[4], "2018", __LINE__);
    helper.IsEqual(storage_str[5], "2018", __LINE__);
    helper.IsEqual(storage_str[6], "2017", __LINE__);

    strings.Reset();

    strings += String<char>("2020");
    strings += String<char>("2017");
    strings += String<char>("2019");
    strings += String<char>("2018");
    strings += String<char>("2021");
    strings += String<char>("2021");
    strings += String<char>("2018");

    strings.Sort(false);
    storage_str = strings.Storage();

    helper.IsEqual(storage_str[0], "2021", __LINE__);
    helper.IsEqual(storage_str[1], "2021", __LINE__);
    helper.IsEqual(storage_str[2], "2020", __LINE__);
    helper.IsEqual(storage_str[3], "2019", __LINE__);
    helper.IsEqual(storage_str[4], "2018", __LINE__);
    helper.IsEqual(storage_str[5], "2018", __LINE__);
    helper.IsEqual(storage_str[6], "2017", __LINE__);
}

static int RunArrayTests() {
    QTest helper{"Array.hpp", __FILE__};

    helper.PrintGroupName();

    helper.Test("Array Test 1", TestArray1);
    helper.Test("Array Test 2", TestArray2);
    helper.Test("Array Test 3", TestArray3);
    helper.Test("Array Test 4", TestArray4);
    helper.Test("Array Sort Test", TestArraySort);

    return helper.EndTests();
}

} // namespace Test
} // namespace Qentem

#endif
