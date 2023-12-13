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
#include "StringStream.hpp"
#include "JSON.hpp"
#include "Template.hpp"

#ifndef QENTEM_TEMPLATE_L_TESTS_H_
#define QENTEM_TEMPLATE_L_TESTS_H_

namespace Qentem {
namespace Test {

static void TestVariableLTag1(QTest &helper) {
    StringStream<wchar_t> ss;

    const wchar_t *content;

    Value<wchar_t> value = JSON::Parse(LR"(["A", "abc", true, 456, 1.5,
           [null, false, ["Qentem"]]])");

    const Value<wchar_t> sub_value =
        JSON::Parse(LR"({"key1": "a", "key2": "ABC", "key3": false, "key4": 100, "key5": 1.5, "key6": {"one": 1}
        ,"key7": [null, false, ["Qentem"]]})");

    value += sub_value;

    content = LR"({var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(A)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:1})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(abc)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:2})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(true)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:3})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(456)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:4})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(1.5)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:5[0]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(null)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:5[1]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(false)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:5[2][0]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(Qentem)", "(Render())", __LINE__);
    ss.Clear();

    //////

    content = LR"({var:key1})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(a)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:key2})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(ABC)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:key3})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(false)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:key4})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(100)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:key5})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(1.5)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:key6[one]})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(1)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:key7[0]})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(null)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:key7[1]})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(false)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:key7[2][0]})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(Qentem)", "(Render())", __LINE__);
    ss.Clear();

    //
    content = LR"({var:6[key1]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(a)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:6[key2]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(ABC)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:6[key3]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(false)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:6[key4]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(100)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:6[key5]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(1.5)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:6[key6][one]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(1)", "(Render())", __LINE__);
    ss.Clear();

    ////////////////

    content = LR"(-{var:2})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(-true)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(-{var:key7[0]})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(-null)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(-{var:key7[2][0]})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(-Qentem)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(-{var:6[key3]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(-false)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(-{var:6[key4]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(-100)", "(Render())", __LINE__);
    ss.Clear();

    ////////////

    content = LR"({var:2}-)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(true-)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:key7[0]}-)";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(null-)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:key7[2][0]}-)";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(Qentem-)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:6[key3]}-)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(false-)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:6[key4]}-)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(100-)", "(Render())", __LINE__);
    ss.Clear();

    ////////////

    content = LR"(-{var:2}-)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(-true-)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(-{var:key7[0]}-)";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(-null-)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(-{var:key7[2][0]}-)";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(-Qentem-)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(-{var:6[key3]}-)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(-false-)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(-{var:6[key4]}-)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(-100-)", "(Render())", __LINE__);
    ss.Clear();

    ////////////

    content = LR"(------{var:2})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(------true)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(------{var:key7[0]})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(------null)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(------{var:key7[2][0]})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(------Qentem)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(------{var:6[key3]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(------false)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(------{var:6[key4]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(------100)", "(Render())", __LINE__);
    ss.Clear();

    ////////////

    content = LR"({var:2}------)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(true------)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:key7[0]}------)";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(null------)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:key7[2][0]}------)";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(Qentem------)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:6[key3]}------)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(false------)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:6[key4]}------)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(100------)", "(Render())", __LINE__);
    ss.Clear();

    ////////////

    content = LR"(------{var:2}------)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(------true------)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(------{var:key7[0]}------)";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(------null------)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(------{var:key7[2][0]}------)";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(------Qentem------)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(------{var:6[key3]}------)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(------false------)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(------{var:6[key4]}------)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(------100------)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:key7[2[0]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var:key7[2[0]})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:6key3]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var:6key3]})", "(Render())", __LINE__);
    ss.Clear();
}

static void TestVariableLTag2(QTest &helper) {
    StringStream<wchar_t> ss;
    const Value<wchar_t>  value = JSON::Parse(LR"(["A", "abc", true, 456, 1.5])");
    const wchar_t        *content;

    content = LR"({var:0}{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(AA)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:1}{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(abcA)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:1}{var:2})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(abctrue)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:2}{var:3}{var:2})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(true456true)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:4}{var:4}{var:4})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(1.51.51.5)", "(Render())", __LINE__);
    ss.Clear();

    ///

    content = LR"({var:0}-{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(A-A)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:1}--{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(abc--A)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:1}---{var:2})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(abc---true)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:2}{var:3}--{var:2})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(true456--true)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:4}--{var:4}{var:4})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(1.5--1.51.5)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:4}--{var:4}--{var:4})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(1.5--1.5--1.5)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:4}---{var:4}---{var:4})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(1.5---1.5---1.5)", "(Render())", __LINE__);
    ss.Clear();
}

static void TestVariableLTag3(QTest &helper) {
    StringStream<wchar_t> ss;
    Value<wchar_t>        value;
    const wchar_t        *content;

    content = LR"({var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var:0})", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({var:a})", value, ss) == LR"({var:a})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:0[0]})";
    helper.EqualsTrue(Template::Render(content, StringUtils::Count(content), value, ss) == LR"({var:0[0]})",
                      "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:a[0]})";
    helper.EqualsTrue(Template::Render(content, StringUtils::Count(content), value, ss) == LR"({var:a[0]})",
                      "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:0[a]})";
    helper.EqualsTrue(Template::Render(content, StringUtils::Count(content), value, ss) == LR"({var:0[a]})",
                      "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:a[abc]})";
    helper.EqualsTrue(Template::Render(content, StringUtils::Count(content), value, ss) == LR"({var:a[abc]})",
                      "(Render())", __LINE__);
    ss.Clear();

    ////////////////

    value = JSON::Parse(LR"([[[]],{"a":["x"],"b":{"a":"X"}}])");

    content = LR"({var:0})";
    helper.EqualsTrue(Template::Render(content, StringUtils::Count(content), value, ss) == LR"({var:0})", "(Render())",
                      __LINE__);
    ss.Clear();

    content = LR"({var:0[0]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var:0[0]})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:0[0][0]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var:0[0][0]})", "(Render())", __LINE__);
    ss.Clear();

    /////

    content = LR"({var:1})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var:1})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:2})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var:2})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:1[a]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var:1[a]})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:1[b]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var:1[b]})", "(Render())", __LINE__);
    ss.Clear();

    ////

    value = JSON::Parse(LR"(["A", "abc", true, 456, 1.5])");

    content = LR"({var:0)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var:0)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(var:0})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({v})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({v})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({va})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({va})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var:})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({v:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({v:0})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({va:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({va:0})", "(Render())", __LINE__);
    ss.Clear();

    ////

    content = LR"({var:0{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var:0{var:0})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(var:0{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(var:0A)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(var:0}{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(var:0}A)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:0{var:0}{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var:0{var:0}A)", "(Render())", __LINE__);
    ss.Clear();

    ////

    content = LR"({var:0{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var:0{var:0})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(var:0{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(var:0A)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(var:0}{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(var:0}A)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:0{var:0}{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var:0{var:0}A)", "(Render())", __LINE__);
    ss.Clear();

    ////

    content = LR"({{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({A)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({{var:0}{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({AA)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({v{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({vA)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({v{var:0}{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({vAA)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({va{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({vaA)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({va{var:0}{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({vaAA)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({varA)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var{var:0}{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({varAA)", "(Render())", __LINE__);
    ss.Clear();

    ///

    content = LR"({-{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({-A)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({-{var:0}{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({-AA)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({v-{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({v-A)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({v-{var:0}{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({v-AA)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({va-{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({va-A)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({va-{var:0}{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({va-AA)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var-{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var-A)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var-{var:0}{var:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var-AA)", "(Render())", __LINE__);
    ss.Clear();

    //

    content = LR"({var-0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var-0})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var 0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var 0})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:0 })";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var:0 })", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:0 )";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var:0 )", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({var:0)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var:0)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"( {var-0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"( {var-0})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"( {var 0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"( {var 0})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"( {var:0 })";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"( {var:0 })", "(Render())", __LINE__);
    ss.Clear();

    content = LR"( {var:0 )";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"( {var:0 )", "(Render())", __LINE__);
    ss.Clear();

    content = LR"( {var:0)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"( {var:0)", "(Render())", __LINE__);
    ss.Clear();
}

static void TestVariableLTag4(QTest &helper) {
    StringStream<wchar_t> ss;
    Value<wchar_t>        value;

    value += LR"(<)";
    value += LR"(>)";
    value += LR"(&)";
    value += LR"(")";
    value += LR"(')";
    value += LR"(<>)";
    value += LR"(<&)";
    value += LR"(<&)";
    value += LR"(>")";
    value += LR"("')";
    value += LR"(<">)";
    value += LR"(<'>)";
    value += LR"(<&>)";
    value += LR"(&"&)";
    value += LR"("'")";
    value += LR"('<')";
    value += LR"('&')";
    value += LR"(<>&'")";
    value += LR"('"<>&)";
    value += LR"(<"&'>)";

    value += LR"(<<<<<)";
    value += LR"(>>>>>)";
    value += LR"(&&&&&)";
    value += LR"(""""")";
    value += LR"(''''')";

    value += LR"(A<)";
    value += LR"(A>)";
    value += LR"(A&)";
    value += LR"(A")";
    value += LR"(A')";
    value += LR"(<A)";
    value += LR"(>A)";
    value += LR"(&A)";
    value += LR"("A)";
    value += LR"('A)";
    value += LR"(A<A)";
    value += LR"(A>A)";
    value += LR"(A&A)";
    value += LR"(A"A)";
    value += LR"(A'A)";

    value += LR"(AA<AA)";
    value += LR"(AA>AA)";
    value += LR"(AA&AA)";
    value += LR"(AA"AA)";
    value += LR"(AA'AA)";

    value += LR"(AA<<<<AA)";
    value += LR"(AA>>>>AA)";
    value += LR"(AA&&&&AA)";
    value += LR"(AA""""AA)";
    value += LR"(AA''''AA)";

    value += LR"(<A>B'C"D&E'F"G<H>I&G"K)";
    value += LR"(AB"CD'EF<GH>IGK')";
    value += LR"("ABC'DEF<GHI>GK<)";
    value += LR"(A""BC<<DE>>FG''HI&&GK)";

    if (Config::AutoEscapeHTML) {
        helper.EqualsTrue(Template::Render(LR"({var:0})", value, ss) == LR"(&lt;)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:1})", value, ss) == LR"(&gt;)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:2})", value, ss) == LR"(&amp;)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:3})", value, ss) == LR"(&quot;)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:4})", value, ss) == LR"(&apos;)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:5})", value, ss) == LR"(&lt;&gt;)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:6})", value, ss) == LR"(&lt;&amp;)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:7})", value, ss) == LR"(&lt;&amp;)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:8})", value, ss) == LR"(&gt;&quot;)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:9})", value, ss) == LR"(&quot;&apos;)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:10})", value, ss) == LR"(&lt;&quot;&gt;)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:11})", value, ss) == LR"(&lt;&apos;&gt;)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:12})", value, ss) == LR"(&lt;&amp;&gt;)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:13})", value, ss) == LR"(&amp;&quot;&amp;)", "(Render())",
                          __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:14})", value, ss) == LR"(&quot;&apos;&quot;)", "(Render())",
                          __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:15})", value, ss) == LR"(&apos;&lt;&apos;)", "(Render())",
                          __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:16})", value, ss) == LR"(&apos;&amp;&apos;)", "(Render())",
                          __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:17})", value, ss) == LR"(&lt;&gt;&amp;&apos;&quot;)", "(Render())",
                          __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:18})", value, ss) == LR"(&apos;&quot;&lt;&gt;&amp;)", "(Render())",
                          __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:19})", value, ss) == LR"(&lt;&quot;&amp;&apos;&gt;)", "(Render())",
                          __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:20})", value, ss) == LR"(&lt;&lt;&lt;&lt;&lt;)", "(Render())",
                          __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:21})", value, ss) == LR"(&gt;&gt;&gt;&gt;&gt;)", "(Render())",
                          __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:22})", value, ss) == LR"(&amp;&amp;&amp;&amp;&amp;)", "(Render())",
                          __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:23})", value, ss) == LR"(&quot;&quot;&quot;&quot;&quot;)",
                          "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:24})", value, ss) == LR"(&apos;&apos;&apos;&apos;&apos;)",
                          "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:25})", value, ss) == LR"(A&lt;)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:26})", value, ss) == LR"(A&gt;)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:27})", value, ss) == LR"(A&amp;)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:28})", value, ss) == LR"(A&quot;)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:29})", value, ss) == LR"(A&apos;)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:30})", value, ss) == LR"(&lt;A)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:31})", value, ss) == LR"(&gt;A)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:32})", value, ss) == LR"(&amp;A)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:33})", value, ss) == LR"(&quot;A)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:34})", value, ss) == LR"(&apos;A)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:35})", value, ss) == LR"(A&lt;A)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:36})", value, ss) == LR"(A&gt;A)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:37})", value, ss) == LR"(A&amp;A)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:38})", value, ss) == LR"(A&quot;A)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:39})", value, ss) == LR"(A&apos;A)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:40})", value, ss) == LR"(AA&lt;AA)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:41})", value, ss) == LR"(AA&gt;AA)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:42})", value, ss) == LR"(AA&amp;AA)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:43})", value, ss) == LR"(AA&quot;AA)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:44})", value, ss) == LR"(AA&apos;AA)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:45})", value, ss) == LR"(AA&lt;&lt;&lt;&lt;AA)", "(Render())",
                          __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:46})", value, ss) == LR"(AA&gt;&gt;&gt;&gt;AA)", "(Render())",
                          __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:47})", value, ss) == LR"(AA&amp;&amp;&amp;&amp;AA)", "(Render())",
                          __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:48})", value, ss) == LR"(AA&quot;&quot;&quot;&quot;AA)",
                          "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:49})", value, ss) == LR"(AA&apos;&apos;&apos;&apos;AA)",
                          "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:50})", value, ss) ==
                              LR"(&lt;A&gt;B&apos;C&quot;D&amp;E&apos;F&quot;G&lt;H&gt;I&amp;G&quot;K)",
                          "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:51})", value, ss) == LR"(AB&quot;CD&apos;EF&lt;GH&gt;IGK&apos;)",
                          "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:52})", value, ss) == LR"(&quot;ABC&apos;DEF&lt;GHI&gt;GK&lt;)",
                          "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:53})", value, ss) ==
                              LR"(A&quot;&quot;BC&lt;&lt;DE&gt;&gt;FG&apos;&apos;HI&amp;&amp;GK)",
                          "(Render())", __LINE__);
        ss.Clear();

    } else {
        helper.EqualsTrue(Template::Render(LR"({var:0})", value, ss) == LR"(<)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:1})", value, ss) == LR"(>)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:2})", value, ss) == LR"(&)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:3})", value, ss) == LR"(")", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:4})", value, ss) == LR"(')", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:5})", value, ss) == LR"(<>)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:6})", value, ss) == LR"(<&)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:7})", value, ss) == LR"(<&)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:8})", value, ss) == LR"(>")", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:9})", value, ss) == LR"("')", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:10})", value, ss) == LR"(<">)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:11})", value, ss) == LR"(<'>)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:12})", value, ss) == LR"(<&>)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:13})", value, ss) == LR"(&"&)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:14})", value, ss) == LR"("'")", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:15})", value, ss) == LR"('<')", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:16})", value, ss) == LR"('&')", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:17})", value, ss) == LR"(<>&'")", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:18})", value, ss) == LR"('"<>&)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:19})", value, ss) == LR"(<"&'>)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:20})", value, ss) == LR"(<<<<<)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:21})", value, ss) == LR"(>>>>>)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:22})", value, ss) == LR"(&&&&&)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:23})", value, ss) == LR"(""""")", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:24})", value, ss) == LR"(''''')", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:25})", value, ss) == LR"(A<)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:26})", value, ss) == LR"(A>)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:27})", value, ss) == LR"(A&)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:28})", value, ss) == LR"(A")", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:29})", value, ss) == LR"(A')", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:30})", value, ss) == LR"(<A)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:31})", value, ss) == LR"(>A)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:32})", value, ss) == LR"(&A)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:33})", value, ss) == LR"("A)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:34})", value, ss) == LR"('A)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:35})", value, ss) == LR"(A<A)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:36})", value, ss) == LR"(A>A)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:37})", value, ss) == LR"(A&A)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:38})", value, ss) == LR"(A"A)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:39})", value, ss) == LR"(A'A)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:40})", value, ss) == LR"(AA<AA)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:41})", value, ss) == LR"(AA>AA)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:42})", value, ss) == LR"(AA&AA)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:43})", value, ss) == LR"(AA"AA)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:44})", value, ss) == LR"(AA'AA)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:45})", value, ss) == LR"(AA<<<<AA)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:46})", value, ss) == LR"(AA>>>>AA)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:47})", value, ss) == LR"(AA&&&&AA)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:48})", value, ss) == LR"(AA""""AA)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:49})", value, ss) == LR"(AA''''AA)", "(Render())", __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:50})", value, ss) == LR"(<A>B'C"D&E'F"G<H>I&G"K)", "(Render())",
                          __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:51})", value, ss) == LR"(AB"CD'EF<GH>IGK')", "(Render())",
                          __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:52})", value, ss) == LR"("ABC'DEF<GHI>GK<)", "(Render())",
                          __LINE__);
        ss.Clear();

        helper.EqualsTrue(Template::Render(LR"({var:53})", value, ss) == LR"(A""BC<<DE>>FG''HI&&GK)", "(Render())",
                          __LINE__);
        ss.Clear();
    }
}

static void TestRawVariableLTag1(QTest &helper) {
    StringStream<wchar_t> ss;
    const wchar_t        *content;

    Value<wchar_t> value = JSON::Parse(LR"(["A", "abc", true, 456, 1.5,
           [null, false, ["Qentem"]]])");

    const Value<wchar_t> sub_value =
        JSON::Parse(LR"({"key1": "a", "key2": "ABC", "key3": false, "key4": 100, "key5": 1.5, "key6": {"one": 1}
        ,"key7": [null, false, ["Qentem"]]})");

    value += sub_value;

    content = LR"({raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(A)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:1})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(abc)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:2})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(true)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:3})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(456)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:4})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(1.5)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:5[0]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(null)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:5[1]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(false)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:5[2][0]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(Qentem)", "(Render())", __LINE__);
    ss.Clear();

    //////

    content = LR"({raw:key1})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(a)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:key2})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(ABC)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:key3})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(false)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:key4})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(100)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:key5})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(1.5)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:key6[one]})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(1)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:key7[0]})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(null)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:key7[1]})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(false)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:key7[2][0]})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(Qentem)", "(Render())", __LINE__);
    ss.Clear();

    //
    content = LR"({raw:6[key1]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(a)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:6[key2]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(ABC)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:6[key3]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(false)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:6[key4]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(100)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:6[key5]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(1.5)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:6[key6][one]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(1)", "(Render())", __LINE__);
    ss.Clear();

    ////////////////

    content = LR"(-{raw:2})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(-true)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(-{raw:key7[0]})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(-null)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(-{raw:key7[2][0]})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(-Qentem)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(-{raw:6[key3]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(-false)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(-{raw:6[key4]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(-100)", "(Render())", __LINE__);
    ss.Clear();

    ////////////

    content = LR"({raw:2}-)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(true-)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:key7[0]}-)";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(null-)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:key7[2][0]}-)";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(Qentem-)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:6[key3]}-)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(false-)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:6[key4]}-)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(100-)", "(Render())", __LINE__);
    ss.Clear();

    ////////////

    content = LR"(-{raw:2}-)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(-true-)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(-{raw:key7[0]}-)";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(-null-)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(-{raw:key7[2][0]}-)";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(-Qentem-)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(-{raw:6[key3]}-)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(-false-)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(-{raw:6[key4]}-)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(-100-)", "(Render())", __LINE__);
    ss.Clear();

    ////////////

    content = LR"(------{raw:2})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(------true)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(------{raw:key7[0]})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(------null)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(------{raw:key7[2][0]})";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(------Qentem)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(------{raw:6[key3]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(------false)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(------{raw:6[key4]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(------100)", "(Render())", __LINE__);
    ss.Clear();

    ////////////

    content = LR"({raw:2}------)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(true------)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:key7[0]}------)";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(null------)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:key7[2][0]}------)";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(Qentem------)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:6[key3]}------)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(false------)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:6[key4]}------)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(100------)", "(Render())", __LINE__);
    ss.Clear();

    ////////////

    content = LR"(------{raw:2}------)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(------true------)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(------{raw:key7[0]}------)";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(------null------)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(------{raw:key7[2][0]}------)";
    helper.EqualsTrue(Template::Render(content, sub_value, ss) == LR"(------Qentem------)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(------{raw:6[key3]}------)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(------false------)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(------{raw:6[key4]}------)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(------100------)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:key7[2[0]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raw:key7[2[0]})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:6key3]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raw:6key3]})", "(Render())", __LINE__);
    ss.Clear();
}

static void TestRawVariableLTag2(QTest &helper) {
    StringStream<wchar_t> ss;
    const Value<wchar_t>  value = JSON::Parse(LR"(["A", "abc", true, 456, 1.5])");
    const wchar_t        *content;

    content = LR"({raw:0}{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(AA)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:1}{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(abcA)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:1}{raw:2})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(abctrue)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:2}{raw:3}{raw:2})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(true456true)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:4}{raw:4}{raw:4})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(1.51.51.5)", "(Render())", __LINE__);
    ss.Clear();

    ///

    content = LR"({raw:0}-{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(A-A)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:1}--{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(abc--A)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:1}---{raw:2})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(abc---true)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:2}{raw:3}--{raw:2})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(true456--true)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:4}--{raw:4}{raw:4})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(1.5--1.51.5)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:4}--{raw:4}--{raw:4})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(1.5--1.5--1.5)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:4}---{raw:4}---{raw:4})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(1.5---1.5---1.5)", "(Render())", __LINE__);
    ss.Clear();
}

static void TestRawVariableLTag3(QTest &helper) {
    StringStream<wchar_t> ss;
    Value<wchar_t>        value;
    const wchar_t        *content;

    content = LR"({raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raw:0})", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:a})", value, ss) == LR"({raw:a})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:0[0]})";
    helper.EqualsTrue(Template::Render(content, StringUtils::Count(content), value, ss) == LR"({raw:0[0]})",
                      "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:a[0]})";
    helper.EqualsTrue(Template::Render(content, StringUtils::Count(content), value, ss) == LR"({raw:a[0]})",
                      "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:0[a]})";
    helper.EqualsTrue(Template::Render(content, StringUtils::Count(content), value, ss) == LR"({raw:0[a]})",
                      "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:a[abc]})";
    helper.EqualsTrue(Template::Render(content, StringUtils::Count(content), value, ss) == LR"({raw:a[abc]})",
                      "(Render())", __LINE__);
    ss.Clear();

    ////////////////

    value = JSON::Parse(LR"([[[]],{"a":["x"],"b":{"a":"X"}}])");

    content = LR"({raw:0})";
    helper.EqualsTrue(Template::Render(content, StringUtils::Count(content), value, ss) == LR"({raw:0})", "(Render())",
                      __LINE__);
    ss.Clear();

    content = LR"({raw:0[0]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raw:0[0]})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:0[0][0]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raw:0[0][0]})", "(Render())", __LINE__);
    ss.Clear();

    /////

    content = LR"({raw:1})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raw:1})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:2})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raw:2})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:1[a]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raw:1[a]})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:1[b]})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raw:1[b]})", "(Render())", __LINE__);
    ss.Clear();

    ////

    value = JSON::Parse(LR"(["A", "abc", true, 456, 1.5])");

    content = LR"({raw:0)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raw:0)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(raw:0})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({r})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({r})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({ra})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({ra})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raw})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raw:})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({r:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({r:0})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({ra:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({ra:0})", "(Render())", __LINE__);
    ss.Clear();

    ////

    content = LR"({raw:0{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raw:0{raw:0})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(raw:0{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(raw:0A)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(raw:0}{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(raw:0}A)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:0{raw:0}{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raw:0{raw:0}A)", "(Render())", __LINE__);
    ss.Clear();

    ////

    content = LR"({raw:0{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raw:0{raw:0})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(raw:0{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(raw:0A)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(raw:0}{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(raw:0}A)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:0{raw:0}{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raw:0{raw:0}A)", "(Render())", __LINE__);
    ss.Clear();

    ////

    content = LR"({{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({A)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({{raw:0}{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({AA)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({r{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({rA)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({r{raw:0}{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({rAA)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({ra{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raA)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({ra{raw:0}{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raAA)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({rawA)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw{raw:0}{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({rawAA)", "(Render())", __LINE__);
    ss.Clear();

    ///

    content = LR"({-{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({-A)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({-{raw:0}{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({-AA)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({r-{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({r-A)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({r-{raw:0}{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({r-AA)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({ra-{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({ra-A)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({ra-{raw:0}{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({ra-AA)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw-{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raw-A)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw-{raw:0}{raw:0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raw-AA)", "(Render())", __LINE__);
    ss.Clear();

    //

    content = LR"({raw-0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raw-0})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw 0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raw 0})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:0 })";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raw:0 })", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:0 )";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raw:0 )", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({raw:0)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({raw:0)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({ raw-0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({ raw-0})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({ raw 0})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({ raw 0})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({ raw:0 })";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({ raw:0 })", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({ raw:0 )";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({ raw:0 )", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({ raw:0)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({ raw:0)", "(Render())", __LINE__);
    ss.Clear();
}

static void TestRawVariableLTag4(QTest &helper) {
    StringStream<wchar_t> ss;
    Value<wchar_t>        value;

    value += LR"(<)";
    value += LR"(>)";
    value += LR"(&)";
    value += LR"(")";
    value += LR"(')";
    value += LR"(<>)";
    value += LR"(<&)";
    value += LR"(<&)";
    value += LR"(>")";
    value += LR"("')";
    value += LR"(<">)";
    value += LR"(<'>)";
    value += LR"(<&>)";
    value += LR"(&"&)";
    value += LR"("'")";
    value += LR"('<')";
    value += LR"('&')";
    value += LR"(<>&'")";
    value += LR"('"<>&)";
    value += LR"(<"&'>)";

    value += LR"(<<<<<)";
    value += LR"(>>>>>)";
    value += LR"(&&&&&)";
    value += LR"(""""")";
    value += LR"(''''')";

    value += LR"(A<)";
    value += LR"(A>)";
    value += LR"(A&)";
    value += LR"(A")";
    value += LR"(A')";
    value += LR"(<A)";
    value += LR"(>A)";
    value += LR"(&A)";
    value += LR"("A)";
    value += LR"('A)";
    value += LR"(A<A)";
    value += LR"(A>A)";
    value += LR"(A&A)";
    value += LR"(A"A)";
    value += LR"(A'A)";

    value += LR"(AA<AA)";
    value += LR"(AA>AA)";
    value += LR"(AA&AA)";
    value += LR"(AA"AA)";
    value += LR"(AA'AA)";

    value += LR"(AA<<<<AA)";
    value += LR"(AA>>>>AA)";
    value += LR"(AA&&&&AA)";
    value += LR"(AA""""AA)";
    value += LR"(AA''''AA)";

    value += LR"(<A>B'C"D&E'F"G<H>I&G"K)";
    value += LR"(AB"CD'EF<GH>IGK')";
    value += LR"("ABC'DEF<GHI>GK<)";
    value += LR"(A""BC<<DE>>FG''HI&&GK)";

    helper.EqualsTrue(Template::Render(LR"({raw:0})", value, ss) == LR"(<)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:1})", value, ss) == LR"(>)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:2})", value, ss) == LR"(&)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:3})", value, ss) == LR"(")", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:4})", value, ss) == LR"(')", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:5})", value, ss) == LR"(<>)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:6})", value, ss) == LR"(<&)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:7})", value, ss) == LR"(<&)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:8})", value, ss) == LR"(>")", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:9})", value, ss) == LR"("')", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:10})", value, ss) == LR"(<">)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:11})", value, ss) == LR"(<'>)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:12})", value, ss) == LR"(<&>)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:13})", value, ss) == LR"(&"&)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:14})", value, ss) == LR"("'")", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:15})", value, ss) == LR"('<')", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:16})", value, ss) == LR"('&')", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:17})", value, ss) == LR"(<>&'")", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:18})", value, ss) == LR"('"<>&)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:19})", value, ss) == LR"(<"&'>)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:20})", value, ss) == LR"(<<<<<)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:21})", value, ss) == LR"(>>>>>)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:22})", value, ss) == LR"(&&&&&)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:23})", value, ss) == LR"(""""")", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:24})", value, ss) == LR"(''''')", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:25})", value, ss) == LR"(A<)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:26})", value, ss) == LR"(A>)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:27})", value, ss) == LR"(A&)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:28})", value, ss) == LR"(A")", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:29})", value, ss) == LR"(A')", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:30})", value, ss) == LR"(<A)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:31})", value, ss) == LR"(>A)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:32})", value, ss) == LR"(&A)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:33})", value, ss) == LR"("A)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:34})", value, ss) == LR"('A)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:35})", value, ss) == LR"(A<A)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:36})", value, ss) == LR"(A>A)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:37})", value, ss) == LR"(A&A)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:38})", value, ss) == LR"(A"A)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:39})", value, ss) == LR"(A'A)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:40})", value, ss) == LR"(AA<AA)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:41})", value, ss) == LR"(AA>AA)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:42})", value, ss) == LR"(AA&AA)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:43})", value, ss) == LR"(AA"AA)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:44})", value, ss) == LR"(AA'AA)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:45})", value, ss) == LR"(AA<<<<AA)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:46})", value, ss) == LR"(AA>>>>AA)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:47})", value, ss) == LR"(AA&&&&AA)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:48})", value, ss) == LR"(AA""""AA)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:49})", value, ss) == LR"(AA''''AA)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:50})", value, ss) == LR"(<A>B'C"D&E'F"G<H>I&G"K)", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:51})", value, ss) == LR"(AB"CD'EF<GH>IGK')", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:52})", value, ss) == LR"("ABC'DEF<GHI>GK<)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({raw:53})", value, ss) == LR"(A""BC<<DE>>FG''HI&&GK)", "(Render())",
                      __LINE__);
    ss.Clear();
}

static void TestMathLTag1(QTest &helper) {
    StringStream<wchar_t> ss;
    Value<wchar_t>        value;

    value[LR"(a1)"] = 5;
    value[LR"(a2)"] = true;
    value[LR"(a3)"] = nullptr;
    value[LR"(a4)"] = false;
    value[LR"(a5)"] = LR"(10)";
    value[LR"(a6)"] = LR"(20)";
    value[LR"(a7)"] = 6;
    value[LR"(a8)"] = 1;
    value[LR"(a9)"] = LR"(1)";

    helper.EqualsTrue(Template::Render(LR"({math:1+1})", value, ss) == LR"(2)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a1}+8})", value, ss) == LR"(13)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a7}+8})", value, ss) == LR"(14)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a7}+{var:a1}})", value, ss) == LR"(11)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a5}+{var:a1}})", value, ss) == LR"(15)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a1}+{var:a5}})", value, ss) == LR"(15)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a6}+{var:a5}})", value, ss) == LR"(30)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a6}*{var:a2}})", value, ss) == LR"(20)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a6}*{var:a4}})", value, ss) == LR"(0)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a6}*{var:a7}})", value, ss) == LR"(120)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a7}+{var:a6}})", value, ss) == LR"(26)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a1}+{var:a2}})", value, ss) == LR"(6)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a8}=={var:a2}})", value, ss) == LR"(1)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a2}=={var:a8}})", value, ss) == LR"(1)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a5}!={var:a1}})", value, ss) == LR"(1)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a2}!={var:a4}})", value, ss) == LR"(1)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a2}==true})", value, ss) == LR"(1)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a9}=={var:a8}})", value, ss) == LR"(1)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a8}=={var:a9}})", value, ss) == LR"(1)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:1=={var:a8}})", value, ss) == LR"(1)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:6-5==({var:a9})})", value, ss) == LR"(1)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:6-5==({var:a8})})", value, ss) == LR"(1)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:null!={var:a3}})", value, ss) == LR"(0)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:({var:a3})==(0)})", value, ss) == LR"(1)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a1}+{var:a7}})", value, ss) == LR"(11)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a1}+{var:a7}}{math:{var:a1}+{var:a7}})", value, ss) == LR"(1111)",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a1}+{var:a7}}*{math:{var:a1}+{var:a7}})", value, ss) ==
                          LR"(11*11)",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a1}+{var:a7}}##{math:{var:a1}+{var:a7}})", value, ss) ==
                          LR"(11##11)",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a1}+{var:a7}}&&&%%^^&&*{math:{var:a1}+{var:a7}})", value, ss) ==
                          LR"(11&&&%%^^&&*11)",
                      "(Render())", __LINE__);
    ss.Clear();

    ///////////////////

    helper.EqualsTrue(Template::Render(LR"({math: {var:a1}+8})", value, ss) == LR"(13)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:  {var:a7}+8})", value, ss) == LR"(14)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:     {var:a7}+{var:a1}})", value, ss) == LR"(11)", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a5} +{var:a1}})", value, ss) == LR"(15)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a1}  +{var:a5}})", value, ss) == LR"(15)", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a6}    +{var:a5}})", value, ss) == LR"(30)", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a6}* {var:a2}})", value, ss) == LR"(20)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a6}*  {var:a4}})", value, ss) == LR"(0)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a6}*      {var:a7}})", value, ss) == LR"(120)", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a7}+{var:a6} })", value, ss) == LR"(26)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a1}+{var:a2}  })", value, ss) == LR"(6)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a8}=={var:a2}      })", value, ss) == LR"(1)", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a2}=={var:a8}})", value, ss) == LR"(1)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math: {var:a5}!={var:a1} })", value, ss) == LR"(1)", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:  {var:a2}!={var:a4}  })", value, ss) == LR"(1)", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:    1=={var:a9}     })", value, ss) == LR"(1)", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a9} == {var:a8}})", value, ss) == LR"(1)", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a8}  ==  {var:a9}})", value, ss) == LR"(1)", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:1==          {var:a8}})", value, ss) == LR"(1)", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:6-5         ==1})", value, ss) == LR"(1)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:1          ==            {var:a8}})", value, ss) == LR"(1)",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:     0     !=    ({var:a3})        })", value, ss) == LR"(0)",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:a3}       ==       null     })", value, ss) == LR"(1)",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:((8+1+{var:a8}))})", value, ss) == LR"(10)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:10==(8+1+{var:a8})})", value, ss) == LR"(1)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:((8+1+{var:a8}))==9+1})", value, ss) == LR"(1)", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:(5*2)==((8+1+{var:a8}))})", value, ss) == LR"(1)", "(Render())",
                      __LINE__);
    ss.Clear();

    //////////////
    value.Reset();

    value += 5;
    value += true;
    value += nullptr;
    value += false;
    value += LR"(10)";
    value += LR"(20)";
    value += 6;
    value += 1;
    value += LR"(1)";
    value += LR"(Qentem)";

    helper.EqualsTrue(Template::Render(LR"({math:{var:0}+8})", value, ss) == LR"(13)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:6}+8})", value, ss) == LR"(14)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:6}+{var:0}})", value, ss) == LR"(11)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:4}+{var:0}})", value, ss) == LR"(15)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:0}+{var:4}})", value, ss) == LR"(15)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:5}+{var:4}})", value, ss) == LR"(30)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:5}*{var:1}})", value, ss) == LR"(20)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:5}*{var:3}})", value, ss) == LR"(0)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:5}*{var:6}})", value, ss) == LR"(120)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:6}+{var:5}})", value, ss) == LR"(26)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:0}+{var:1}})", value, ss) == LR"(6)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:7}=={var:1}})", value, ss) == LR"(1)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:1}=={var:7}})", value, ss) == LR"(1)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:4}!={var:0}})", value, ss) == LR"(1)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:1}!={var:3}})", value, ss) == LR"(1)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:({var:1})==({var:8})})", value, ss) == LR"(1)", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"(-{math:{var:8}=={var:7}})", value, ss) == LR"(-1)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"(--{math:{var:7}=={var:8}})", value, ss) == LR"(--1)", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"(---{math:1=={var:7}})", value, ss) == LR"(---1)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:1==({var:8})}-)", value, ss) == LR"(1-)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:6-5==({var:7})}--)", value, ss) == LR"(1--)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:0==({var:2})}---)", value, ss) == LR"(1---)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"(-{math:{var:2}!=null}-)", value, ss) == LR"(-0-)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"(--{math:Qente=={var:9}}--)", value, ss) == LR"(--0--)", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"(---{math:Qente !={var:9}}---)", value, ss) == LR"(---1---)", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:  Qentem   =={var:9}})", value, ss) == LR"(1)", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:  Qentem!={var:9}})", value, ss) == LR"(0)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:9}   ==    Qente})", value, ss) == LR"(0)", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:9} !=    Qente    })", value, ss) == LR"(1)", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:  {var:9}   ==Qentem})", value, ss) == LR"(1)", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math: {var:9} !=Qentem})", value, ss) == LR"(0)", "(Render())", __LINE__);
    ss.Clear();

    /////////

    helper.EqualsTrue(Template::Render(LR"({math: true == {var:1}})", value, ss) == LR"(1)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math: {var:1} == true})", value, ss) == LR"(1)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math: 8 /2})", value, ss) == LR"(4)", "(Render())", __LINE__);
}

static void TestMathLTag2(QTest &helper) {
    StringStream<wchar_t> ss;
    Value<wchar_t>        value;

    value += Array<Value<wchar_t>>();
    value += HArray<Value<wchar_t>, wchar_t>();
    value += 5;

    helper.EqualsTrue(Template::Render(LR"({math:{var:0}+8})", value, ss) == LR"({math:{var:0}+8})", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:1}+8})", value, ss) == LR"({math:{var:1}+8})", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:2}+{var:0}})", value, ss) == LR"({math:{var:2}+{var:0}})",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:2}+{var:0}})", value, ss) == LR"({math:{var:2}+{var:0}})",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:0}+{var:1}})", value, ss) == LR"({math:{var:0}+{var:1}})",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:1}+{var:2}})", value, ss) == LR"({math:{var:1}+{var:2}})",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:2}*{var:1}})", value, ss) == LR"({math:{var:2}*{var:1}})",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:0}*{var:1}})", value, ss) == LR"({math:{var:0}*{var:1}})",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:0}*{var:2}})", value, ss) == LR"({math:{var:0}*{var:2}})",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:2}+{var:0}})", value, ss) == LR"({math:{var:2}+{var:0}})",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:1}+{var:2}})", value, ss) == LR"({math:{var:1}+{var:2}})",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:0}=={var:1}})", value, ss) == LR"({math:{var:0}=={var:1}})",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:1}=={var:0}})", value, ss) == LR"({math:{var:1}=={var:0}})",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:0}!={var:2}})", value, ss) == LR"({math:{var:0}!={var:2}})",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:2}!={var:0}})", value, ss) == LR"({math:{var:2}!={var:0}})",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:1}=={var:2}})", value, ss) == LR"({math:{var:1}=={var:2}})",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:8}=={var:7}})", value, ss) == LR"({math:{var:8}=={var:7}})",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:7}=={var:2}})", value, ss) == LR"({math:{var:7}=={var:2}})",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:1=={var:7}})", value, ss) == LR"({math:1=={var:7}})", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:(6-5)=={var:8}})", value, ss) == LR"({math:(6-5)=={var:8}})",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:(6-5)=={var:0}})", value, ss) == LR"({math:(6-5)=={var:0}})",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:0}=={var:8}})", value, ss) == LR"({math:{var:0}=={var:8}})",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:0}=={var:0}})", value, ss) == LR"({math:{var:0}=={var:0}})",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:0=={var:1}})", value, ss) == LR"({math:0=={var:1}})", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:1}!=0})", value, ss) == LR"({math:{var:1}!=0})", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:W={var:0}})", value, ss) == LR"({math:W={var:0}})", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:W=={var:0}})", value, ss) == LR"({math:W=={var:0}})", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:2}==c})", value, ss) == LR"({math:{var:2}==c})", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:abc=={var:2}})", value, ss) == LR"({math:abc=={var:2}})", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:sds})", value, ss) == LR"({math:sds})", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:1)", value, ss) == LR"({math:1)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"(math:1})", value, ss) == LR"(math:1})", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:{var:2})", value, ss) == LR"({math:5)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({{math:{var:2}+5})", value, ss) == LR"({10)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({m{var:2}})", value, ss) == LR"({m5})", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({ma{var:2}})", value, ss) == LR"({ma5})", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({mat{var:2}})", value, ss) == LR"({mat5})", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math{var:2}})", value, ss) == LR"({math5})", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math {var:2}})", value, ss) == LR"({math 5})", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:})", value, ss) == LR"({math:})", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math-{var:2}}{math:{var:2}+5})", value, ss) == LR"({math-5}10)",
                      "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math-4}{math:{var:2}+5})", value, ss) == LR"({math-4}10)", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math-4} {math:{var:2}+5})", value, ss) == LR"({math-4} 10)", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:4)", value, ss) == LR"({math:4)", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:4    )", value, ss) == LR"({math:4    )", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:A==1+1})", value, ss) == LR"({math:A==1+1})", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:(A)!=1+1})", value, ss) == LR"({math:(A)!=1+1})", "(Render())",
                      __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:1+1==A})", value, ss) == LR"({math:1+1==A})", "(Render())", __LINE__);
    ss.Clear();

    helper.EqualsTrue(Template::Render(LR"({math:1+1!=(A)})", value, ss) == LR"({math:1+1!=(A)})", "(Render())",
                      __LINE__);
    ss.Clear();
}

static void TestInlineIfLTag(QTest &helper) {
    StringStream<wchar_t> ss;
    Value<wchar_t>        value;
    const wchar_t        *content;

    value += 0;
    value += 1;
    value += -1;
    value += true;
    value += false;
    value += nullptr;
    value += LR"(ABC)";
    value += Array<Value<wchar_t>>();

    content = LR"({if case="0" true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(F)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="-1" true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(F)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="0.1" true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(T)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="1" true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(T)", "(Render())", __LINE__);
    ss.Clear();

    ////

    content = LR"({if case="0" true="T"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="-1" true="T"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="0.1" true="T"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(T)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="1" true="T"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(T)", "(Render())", __LINE__);
    ss.Clear();

    ///

    content = LR"({if case="0" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(F)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="-1" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(F)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="0.1" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="1" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();

    /////

    content = LR"({if case="{var:0}" true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(F)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="{var:2}" true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(F)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="{raw:4}" true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(F)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="{var:5}" true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(F)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="{var:5}" true="T" false="{F}"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({F})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="{var:6}" true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="fas" true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="{var:7}" true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="{var:20}" true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();

    ////
    content = LR"({if case="{var:1}" true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(T)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="{var:3}" true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(T)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="{var:6}==ABC" true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(T)", "(Render())", __LINE__);
    ss.Clear();

    /////////////////

    content = LR"({if case=" {var:1}" true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(T)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="{var:1} " true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(T)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case=" {var:1} " true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(T)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="  {var:1}" true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(T)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="{var:1}  " true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(T)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="  {var:1}  " true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(T)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="      {var:1}" true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(T)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="{var:1}          " true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(T)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="    {var:1}        " true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(T)", "(Render())", __LINE__);
    ss.Clear();

    ////

    content = LR"(-{if case=" {var:1} " true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(-T)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case=" {var:1} " true="T" false="F"}-)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(T-)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(-{if case=" {var:1} " true="T" false="F"}-)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(-T-)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(--{if case=" {var:1} " true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(--T)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case=" {var:1} " true="T" false="F"}--)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(T--)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(--{if case=" {var:1} " true="T" false="F"}--)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(--T--)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(---{if case=" {var:1} " true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(---T)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case=" {var:1} " true="T" false="F"}---)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(T---)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(---{if case=" {var:1} " true="T" false="F"}---)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(---T---)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="1" true="T"}{if case="0" false="F"}{if case="1" true="T"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(TFT)", "(Render())", __LINE__);
    ss.Clear();

    ///////

    content = LR"({if case="{var:7}" true="T" false="F"}{if case="{var:1}" true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(T)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="01" true="{var:3}" false="{var:4}"}--)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(--)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="" true="c" false="d"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({i)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({i)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({if)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({{if case="{var:1}" true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({T)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({i{if case="{var:1}" true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({iT)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if{if case="{var:1}" true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({ifT)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="{var:1}"                    put="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if{if case="1" true="T" false="F"}}{if case="1" true="T" false="F"})";

    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(TT)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if{if case="{raw:1}" true="T" false="F"}{if case="{var:1}" true="T" false="F"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({ifTT)", "(Render())", __LINE__);
    ss.Clear();

    /////
    content = LR"({if case="0" true="{var:3}" false="{var:4}"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(false)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="1" true="{var:3}" false="{var:4}"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(true)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="0" true="{raw:3}{raw:3}" false="{var:4}{var:4}"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(falsefalse)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="1000" true="{var:3}{var:3}" false="{var:4}{var:4}"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(truetrue)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="0" true="{var:3}---{var:3}" false="{var:4}---{var:4}"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(false---false)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="1" true="{var:3}---{var:3}" false="{var:4}---{var:4}"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(true---true)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="0" true="{var:10}" false="{var:20}"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var:20})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="1" true="{var:10}" false="{var:20}"})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({var:10})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="1" true="1" false="0")";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({if case="1" true="1" false="0")", "(Render())",
                      __LINE__);
    ss.Clear();

    content = LR"({if case="1" true="1" false="0")";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"({if case="1" true="1" false="0")", "(Render())",
                      __LINE__);
    ss.Clear();

    ///////
    Value<wchar_t> value2;

    value2 += LR"(&)";
    value2 += LR"(")";
    value2 += 10;
    value2 += 5;
    value2 += 15;

    content = LR"({if case="1" true="{var:0}" false="{var:1}"})";

    if (Config::AutoEscapeHTML) {
        helper.EqualsTrue(Template::Render(content, value2, ss) == LR"(&amp;)", "(Render())", __LINE__);
        ss.Clear();

    } else {
        helper.EqualsTrue(Template::Render(content, value2, ss) == LR"(&)", "(Render())", __LINE__);
        ss.Clear();
    }

    content = LR"({if case="1" true="{raw:0}" false="{raw:1}"})";
    helper.EqualsTrue(Template::Render(content, value2, ss) == LR"(&)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="0" true="{var:0}" false="{var:1}"})";

    if (Config::AutoEscapeHTML) {
        helper.EqualsTrue(Template::Render(content, value2, ss) == LR"(&quot;)", "(Render())", __LINE__);
        ss.Clear();

    } else {
        helper.EqualsTrue(Template::Render(content, value2, ss) == LR"(")", "(Render())", __LINE__);
        ss.Clear();
    }

    content = LR"({if case="0" true="*{raw:0}*" false="-{raw:1}-"})";
    helper.EqualsTrue(Template::Render(content, value2, ss) == LR"(-"-)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"({if case="0" true="{raw:0}" false="{raw:1}"})";
    helper.EqualsTrue(Template::Render(content, value2, ss) == LR"(")", "(Render())", __LINE__);
    ss.Clear();

    content =
        LR"({if case="{var:2}+{var:3} == {var:4}" true="{math:{var:3}+{var:4}}" false="{math: {var:2}+{var:4}}"})";
    helper.EqualsTrue(Template::Render(content, value2, ss) == LR"(20)", "(Render())", __LINE__);
    ss.Clear();

    content =
        LR"({if case=" {var:4}-{var:3} != {var:2} " true="{math: {var:3}+{var:4} } " false=" {math: {var:2}+{var:4} } "})";
    helper.EqualsTrue(Template::Render(content, value2, ss) == LR"( 25 )", "(Render())", __LINE__);
    ss.Clear();
}

static void TestLoopLTag1(QTest &helper) {
    StringStream<wchar_t> ss;
    Value<wchar_t>        value3;
    const wchar_t        *content;
    Value<wchar_t>        value1;

    value1 += 100;
    value1 += -50;
    value1 += LR"(Qentem)";
    value1 += true;
    value1 += false;
    value1 += nullptr;
    value1 += 3;

    content = LR"(<loop value="loop1-value">{var:loop1-value}, </loop>)";
    helper.EqualsTrue(Template::Render(content, value1, ss) == LR"(100, -50, Qentem, true, false, null, 3, )",
                      "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<loop value="loop1-value">{var:loop1-value}, {var:loop1-value} </loop>)";
    helper.EqualsTrue(Template::Render(content, value1, ss) ==
                          LR"(100, 100 -50, -50 Qentem, Qentem true, true false, false null, null 3, 3 )",
                      "(Render())", __LINE__);
    ss.Clear();

    ////////////////

    value1.Reset();
    value1 += 0;
    value1 += 1;

    content =
        LR"(<loop value="loop1-value"><loop value="loop2-value">({var:loop1-value}: {var:loop2-value}) </loop></loop>)";
    helper.EqualsTrue(Template::Render(content, value1, ss) == LR"((0: 0) (0: 1) (1: 0) (1: 1) )", "(Render())",
                      __LINE__);
    ss.Clear();

    content = LR"(<loop value="loop1-value"><loop value="loop2-value"><loop
                 value="loop3-value">({var:loop1-value}: {var:loop2-value}: {var:loop3-value}) </loop></loop></loop>)";
    helper.EqualsTrue(Template::Render(content, value1, ss) ==
                          LR"((0: 0: 0) (0: 0: 1) (0: 1: 0) (0: 1: 1) (1: 0: 0) (1: 0: 1) (1: 1: 0) (1: 1: 1) )",
                      "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<loop value="loop1-value"><loop value="loop2-value"><loop
                 value="loop3-value"><loop value="loop4-value">({var:loop1-value}: {var:loop2-value}: {var:loop3-value}: {var:loop4-value}) </loop></loop></loop></loop>)";
    helper.EqualsTrue(
        Template::Render(content, value1, ss) ==
            LR"((0: 0: 0: 0) (0: 0: 0: 1) (0: 0: 1: 0) (0: 0: 1: 1) (0: 1: 0: 0) (0: 1: 0: 1) (0: 1: 1: 0) (0: 1: 1: 1) (1: 0: 0: 0) (1: 0: 0: 1) (1: 0: 1: 0) (1: 0: 1: 1) (1: 1: 0: 0) (1: 1: 0: 1) (1: 1: 1: 0) (1: 1: 1: 1) )",
        "(Render())", __LINE__);
    ss.Clear();

    //////////////////////

    value1 = JSON::Parse(LR"([100, -50, "A", true, false, null])");
    const Value<wchar_t> value2 =
        JSON::Parse(LR"({"k-1": 4, "k-2":1.5, "k-3":"ABC", "k-4":true, "k-5":false, "k-6":null})");

    //////////////////////
    value3[LR"(arr1)"] = value1;

    content = LR"(<loop value="loop1-value">{var:loop1-value}, </loop>)";
    helper.EqualsTrue(Template::Render(content, value1, ss) == LR"(100, -50, A, true, false, null, )", "(Render())",
                      __LINE__);
    ss.Clear();

    content = LR"(<loop value="loop1-value">{var:loop1-value}, </loop>)";
    helper.EqualsTrue(Template::Render(content, value2, ss) == LR"(4, 1.5, ABC, true, false, null, )", "(Render())",
                      __LINE__);
    ss.Clear();

    content = LR"(<loop set="arr1" value="loop1-value">{var:loop1-value}, </loop>)";
    helper.EqualsTrue(Template::Render(content, value3, ss) == LR"(100, -50, A, true, false, null, )", "(Render())",
                      __LINE__);
    ss.Clear();

    value3[LR"(arr1)"] = value2;

    content = LR"(<loop set="arr1" value="loop1-value">{var:loop1-value}, </loop>)";
    helper.EqualsTrue(Template::Render(content, value3, ss) == LR"(4, 1.5, ABC, true, false, null, )", "(Render())",
                      __LINE__);
    ss.Clear();

    //////////////////////
    value3[LR"(arr1)"] = value1;

    content = LR"(<loop value="loop1-value" >{var:loop1-value}, </loop>)";
    helper.EqualsTrue(Template::Render(content, value1, ss) == LR"(100, -50, A, true, false, null, )", "(Render())",
                      __LINE__);
    ss.Clear();

    content = LR"(<loop value="loop1-value">{var:loop1-value}, </loop>)";
    helper.EqualsTrue(Template::Render(content, value2, ss) == LR"(4, 1.5, ABC, true, false, null, )", "(Render())",
                      __LINE__);
    ss.Clear();

    content = LR"(<loop value="loop1-value"set="arr1">{var:loop1-value}, </loop>)";
    helper.EqualsTrue(Template::Render(content, value3, ss) == LR"(100, -50, A, true, false, null, )", "(Render())",
                      __LINE__);
    ss.Clear();

    value3[LR"(arr1)"] = value2;

    content = LR"(<loop set="arr1" value="loop1-value">{var:loop1-value}, </loop>)";
    helper.EqualsTrue(Template::Render(content, value3, ss) == LR"(4, 1.5, ABC, true, false, null, )", "(Render())",
                      __LINE__);
    ss.Clear();

    //////////////////////
    value3.Reset();
    value3[LR"(arr1)"][LR"(arr2)"][LR"(arr3)"] = value1;

    content = LR"(<loop set="arr1[arr2][arr3]" value="loop1-value">{var:loop1-value}, </loop>)";
    helper.EqualsTrue(Template::Render(content, value3, ss) == LR"(100, -50, A, true, false, null, )", "(Render())",
                      __LINE__);
    ss.Clear();

    value3.Reset();
    value3[0][0] += value2;

    content = LR"(<loop set="0[0][0]"value="loop1-value">{var:loop1-value}, </loop>)";
    helper.EqualsTrue(Template::Render(content, value3, ss) == LR"(4, 1.5, ABC, true, false, null, )", "(Render())",
                      __LINE__);
    ss.Clear();

    value3.Reset();
    value3[LR"(k1)"][0][LR"(k3)"] = value1;

    content = LR"(<loop value="loop1-value" set="k1[0][k3]">{var:loop1-value}, </loop>)";
    helper.EqualsTrue(Template::Render(content, value3, ss) == LR"(100, -50, A, true, false, null, )", "(Render())",
                      __LINE__);
    ss.Clear();

    value3.Reset();
    value3[0][LR"(k2)"] += value2;

    content = LR"(<loop set="0[k2][0]"value="loop1-value">{var:loop1-value}, {var:loop1-value}, </loop>)";
    helper.EqualsTrue(Template::Render(content, value3, ss) ==
                          LR"(4, 4, 1.5, 1.5, ABC, ABC, true, true, false, false, null, null, )",
                      "(Render())", __LINE__);
    ss.Clear();

    value3 = JSON::Parse(LR"({"group":[[10],[20],[30]]})");

    content = LR"(<loop set="group" value="_Val1"><loop set="_Val1" value="_Val2">{var:_Val2}</loop></loop>)";
    helper.EqualsTrue(Template::Render(content, value3, ss) == LR"(102030)", "(Render())", __LINE__);
    ss.Clear();

    value3 = JSON::Parse(LR"({"group":[1,2,3,4]})");

    content = LR"(<loop set="group" value="_Val">{var:_Val}</loop>)";
    helper.EqualsTrue(Template::Render(content, value3, ss) == LR"(1234)", "(Render())", __LINE__);
    ss.Clear();

    value3  = JSON::Parse(LR"({"numbers":[1,2,3,4,5,6,7,8]})");
    content = LR"(A<loop set="numbers" value="l_id1">{var:l_id1}</loop>B)";
    helper.EqualsTrue(Template::Render(content, value3, ss) == LR"(A12345678B)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<loop set="numbers" value="l_id1">{var:l_id1[0]}</loop>)";
    helper.EqualsTrue(
        Template::Render(content, value3, ss) ==
            LR"({var:l_id1[0]}{var:l_id1[0]}{var:l_id1[0]}{var:l_id1[0]}{var:l_id1[0]}{var:l_id1[0]}{var:l_id1[0]}{var:l_id1[0]})",
        "(Render())", __LINE__);
    ss.Clear();
}

static void TestLoopLTag2(QTest &helper) {
    StringStream<wchar_t> ss;
    Value<wchar_t>        value;
    const wchar_t        *content;

    content = LR"(<loop></loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<loop>abcd</loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<l</loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(<l</loop>)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<lo</loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(<lo</loop>)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<loo</loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(<loo</loop>)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<loop></loop><loop>A</loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<loop value="a">{var:a}</loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<loop set="ss" value="a">{var:a}</loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<loop set="" value="a">{var:a}</loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();

    value[LR"(in)"] = Array<Value<wchar_t>>();

    content = LR"(<loop value="v">{var:v}</loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(in)", "(Render())", __LINE__);
    ss.Clear();

    value.Reset();

    /////
    value.Reset();
    value[LR"(k1)"] = 10;
    value[LR"(k2)"] = 20;
    value[LR"(k3)"] = 30;

    value[LR"(k2)"].Reset();

    content = LR"(<loop value="v">{var:v}</loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(1030)", "(Render())", __LINE__);
    ss.Clear();

    value.RemoveIndex(1);

    content = LR"(<loop value="v">{var:v})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(<loop value="v">{var:v})", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<loop value="v">{var:v}     )";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(<loop value="v">{var:v}     )", "(Render())",
                      __LINE__);
    ss.Clear();

    value.Reset();
    value += 10;
    value += 20;
    value += 30;

    value.RemoveIndex(1);

    content = LR"(<loop value="v">{var:v}</loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(1030)", "(Render())", __LINE__);
    ss.Clear();

    value = JSON::Parse(LR"(
{
    "object": [
        {
            "var1": "value1",
            "var2": "value2",
            "var3": "value3",
            "var4": "value4"
        }
    ],
    "array": [
        [
            "value10",
            "value20",
            "value30",
            "value40"
        ]
    ]
}
    )");

    content =
        LR"(<loop set="object" value="item">{var:item[var1]}{var:item[var2]}{var:item[var3]} {var:item[var4]}</loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(value1value2value3 value4)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<loop set="array" value="item"> {var:item[0]} {var:item[1]} {var:item[2]} {var:item[3]} </loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"( value10 value20 value30 value40 )", "(Render())",
                      __LINE__);
    ss.Clear();

    content =
        LR"(<loop set="object" value="item">{var:item[var11]}{var:item[var22]}{var:item[var33]} {var:item[var44]}</loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) ==
                          LR"({var:item[var11]}{var:item[var22]}{var:item[var33]} {var:item[var44]})",
                      "(Render())", __LINE__);
    ss.Clear();

    content =
        LR"(<loop set="array" value="item">{var:item[var11]}{var:item[var22]}{var:item[var33]} {var:item[var44]}</loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) ==
                          LR"({var:item[var11]}{var:item[var22]}{var:item[var33]} {var:item[var44]})",
                      "(Render())", __LINE__);
    ss.Clear();

    value.RemoveIndex(0);
    content = LR"(<loop><l</loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(<l)", "(Render())", __LINE__);
    ss.Clear();

    value = JSON::Parse(LR"(
{
    "name": "some_val",
    "2020": [
        {
            "month": 5
        },
        {
            "month": 6
        },
        {
            "month": 7
        }
    ]
}
    )");

    content = LR"(<loop set="2020">{var:name}</loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(some_valsome_valsome_val)", "(Render())", __LINE__);
    ss.Clear();

    constexpr SizeT32 size_4 = (8 * 4);

    StringStream<wchar_t> content2;
    StringStream<wchar_t> output;
    Value<wchar_t>        value2;

    for (SizeT32 i = 0; i < size_4; i++) {
        value2 += i;
    }

    content2 += LR"(<loop value="loop1-value">A {var:loop1-value} B</loop>)";
    for (SizeT32 i = 0; i < size_4; i++) {
        output += LR"(A )";
        Digit::NumberToString(output, i);
        output += LR"( B)";
    }

    helper.EqualsTrue(Template::Render(content2.First(), content2.Length(), value2, ss) == output, "(Render())",
                      __LINE__);
    ss.Clear();
}

static void TestLoopLTag3(QTest &helper) {
    StringStream<wchar_t> ss;
    const wchar_t        *content;
    Value<wchar_t>        value = JSON::Parse(LR"(
[
    {
        "year": 2019,
        "quarter": "q1",
        "week": 1,
        "total": 100
    },
    {
        "year": 2019,
        "quarter": "q1",
        "week": 1,
        "total": 125
    },
    {
        "year": 2019,
        "quarter": "q2",
        "week": 1,
        "total": 200
    },
    {
        "year": 2017,
        "quarter": "q2",
        "week": 2,
        "total": 300
    },
    {
        "year": 2020,
        "quarter": "q1",
        "week": 1,
        "total": 400
    },
    {
        "year": 2020,
        "quarter": "q1",
        "week": 1,
        "total": 450
    },
    {
        "year": 2020,
        "quarter": "q1",
        "week": 1,
        "total": 450
    },
    {
        "year": 2018,
        "quarter": "q2",
        "week": 1,
        "total": 200
    },
    {
        "year": 2018,
        "quarter": "q2",
        "week": 2,
        "total": 300
    },
    {
        "year": 2019,
        "quarter": "q2",
        "week": 2,
        "total": 300
    }
]
    )");

    content =
        LR"(<loop value="val1_" group="year111" sort="descend"><loop set="val1_" value="val2_"><loop set="val2_" value="val3_">{var:val3_}</loop></loop></loop>)";

    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();

    content =
        LR"(<loop value="val1_" group="year" sort="descend"><loop set="val1_" value="val2_"><loop set="val2_" value="val3_">{var:val3_}</loop></loop></loop>)";

    helper.EqualsTrue(Template::Render(content, value, ss) ==
                          LR"(q11400q11450q11450q11100q11125q21200q22300q21200q22300q22300)",
                      "(Render())", __LINE__);
    ss.Clear();

    content =
        LR"(<loop value="val1_" group="year" sort="descend"><loop set="val1_" value="val2_" group="quarter" sort="ascend"><loop set="val2_" value="val3_"><loop set="val3_" value="val4_">{var:val4_}</loop></loop></loop></loop>)";

    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(1400145014501100112512002300120023002300)",
                      "(Render())", __LINE__);
    ss.Clear();

    content =
        LR"(<loop value="val1_" group="year" sort="descend">-- {var:val1_}-<loop set="val1_" value="val2_" group="quarter" sort="ascend">{var:val2_}-<loop set="val2_" value="val3_" group="week" sort="ascend">{var:val2_}:<loop set="val3_" value="val4_"><loop set="val4_" value="val5_"> {var:val5_}</loop></loop></loop></loop></loop>)";

    helper.EqualsTrue(
        Template::Render(content, value, ss) ==
            LR"(-- 2020-q1-1: 400 450 450-- 2019-q1-1: 100 125q2-1: 2002: 300-- 2018-q2-1: 2002: 300-- 2017-q2-2: 300)",
        "(Render())", __LINE__);
    ss.Clear();

    content =
        LR"(<loop value="val1_" group="year">-- {var:val1_}-<loop set="val1_" value="val2_" group="quarter">{var:val2_}-<loop set="val2_" value="val3_" group="week">{var:val2_}:<loop set="val3_" value="val4_"><loop set="val4_" value="val5_"> {var:val5_}</loop></loop></loop></loop></loop>)";

    helper.EqualsTrue(
        Template::Render(content, value, ss) ==
            LR"(-- 2019-q1-1: 100 125q2-1: 2002: 300-- 2017-q2-2: 300-- 2020-q1-1: 400 450 450-- 2018-q2-1: 2002: 300)",
        "(Render())", __LINE__);
    ss.Clear();

    ////////////

    value.Reset();

    value += 4;
    value += 1;
    value += 3;
    value += 5;
    value += 2;
    value += 7;
    value += 6;

    content = LR"(<loop value="val1_" sort="a">{var:val1_}</loop>)";

    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(1234567)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<loop value="val1_" sort="d">{var:val1_}</loop>)";

    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(7654321)", "(Render())", __LINE__);
    ss.Clear();
}

static void TestIfLTag1(QTest &helper) {
    StringStream<wchar_t> ss;
    Value<wchar_t>        value;
    const wchar_t        *content;

    value[LR"(name)"] = LR"(Qen)";
    value[LR"(t)"]    = true;
    value[LR"(f)"]    = false;
    value[LR"(n)"]    = nullptr;
    value[LR"(1)"]    = 1;
    value[LR"(one)"]  = LR"(1)";
    value[LR"(zero)"] = 0;

    content = LR"(<if case="1>0">{var:name}</if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(Qen)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(#<if case="{var:one}">{var:name}</if>#)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(#Qen#)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(##<if case="{var:zero}">{var:name}</if>##)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(####)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="{var:1}">{var:name}1<else />{var:name}2</if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(Qen1)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="{var:f}">{var:name}1<else />{var:name}2</if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(Qen2)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(#<if case="{var:t}">G<if case="1">oo</if>d</if>!#)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(#Good!#)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(###<if case="1">G<if case="1">o</if>o<if case="1">d!</if></if>###)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(###Good!###)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(Be <if case="1">G<if case="1">oo<if case="1">d</if></if></if>!)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(Be Good!)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="1">Good!<elseif case="0" />Bad!</if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(Good!)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="{var:n}">Bad!<elseif case="1" />Good!</if>#)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(Good!#)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="{var:f}">Bad!<elseif case="0" />Very Bad!</if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(#<if case="0">Bad!<elseif case="0" />Very Bad!<else />Very Good!</if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(#Very Good!)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="1">a<else />b</if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(a)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="0">a<else />b</if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(b)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="0">a<else /><if case="1">b</if></if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(b)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="1">a<else /><if case="1">b</if></if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(a)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="0">a<if case="1">b</if>c</if>Empty)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(Empty)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="1">a<else /><if case="1">b</if>c</if>===========)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(a===========)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(===========<if case="1">a<if case="1">b</if><else />c</if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(===========ab)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="1">a<elseif case="1" />b<elseif case="1" />c<else />d</if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(a)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="0">a<elseif case="1" />b<elseif case="1" />c<else />d</if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(b)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(===========<if case="0">a<elseif case="0" />b<elseif case="1" />c<else />d</if>===========)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(===========c===========)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="0">a<elseif case="0" />b<elseif case="0" />c<else />d</if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(d)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="1">a<if case="0">b<elseif case="0"/>c</if></if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(a)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="1">a<if case="1">b<elseif case="0"/>c</if></if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(ab)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="1"><if case="1">b<elseif case="c"/>c</if>a<else />c</if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(ba)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="0">a<else />c<if case="1">b<elseif case="0"/>c</if></if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(cb)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if_case="1"><if case="0">Bad1!<elseif case="0" />Bad2!</if>a</if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(a)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="1">
                <if case="0">Bad1!
                <elseif case="0" />Bad2!
                <elseif case="0" />Bad3!
                </if>a<elseif case="1" />b
                <if case="1">Bad1!
                <elseif case="1"/>Bad2!
                <elseif case="1" />Bad3!
                </if>
            <elseif case="1" />
                <if case="1">Bad1!
                <elseif case="1" />Bad2!
                <elseif case="1" />Bad3!
                </if>c
            <else />d
                <if case="1">Bad1!
                <elseif case="1" />Bad2!
                <elseif case="1" />Bad3!
                </if>
            </if>)";
    helper.EqualsTrue(String<wchar_t>::Trim(Template::Render(content, value, ss).GetString()) == LR"(a)", "(Render())",
                      __LINE__);
    ss.Clear();

    content = LR"(<if case="0">a
                <if case="1">Bad1!
                <elseif case="1" />Bad2!
                <else/>Bad3!
                </if>
            <elseif case="1" />
                <if case="0">Bad1!
                <elseif case="0"/>Bad2!
                <elseif case="0" />Bad3!
                </if>b
            <elseif case="1" />c
                <if case="1">Bad1!
                <elseif case="1" />Bad2!
                <elseif case="1" />Bad3!
                </if>
            <else />
                <if case="1">Bad1!
                <elseif case="1" />Bad2!
                <elseif case="1" />Bad3!
                </if>d
            </if>)";
    helper.EqualsTrue(String<wchar_t>::Trim(Template::Render(content, value, ss).GetString()) == LR"(b)", "(Render())",
                      __LINE__);
    ss.Clear();

    content = LR"(<if case="0">
                <if case="1">Bad1!
                <elseif case="1" />Bad2!
                <else/>Bad3!
                </if>a
            <elseif case="0" />b
                <if case="1">Bad1!
                <elseif case="1"/>Bad2!
                <else/>Bad3!
                </if>
            <elseif case="1" />
                <if case="0">Bad1!
                <elseif case="0" />Bad2!
                <elseif case="0" />Bad3!
                </if>c
            <else />d
                <if case="1">Bad1!
                <elseif case="1" />Bad2!
                <else/>Bad3!
                </if>
            </if>)";
    helper.EqualsTrue(String<wchar_t>::Trim(Template::Render(content, value, ss).GetString()) == LR"(c)", "(Render())",
                      __LINE__);
    ss.Clear();

    content = LR"(<if case="0">a
                <if case="1">Bad1!
                <elseif case="1" />Bad2!
                <else/>Bad3!
                </if>
            <elseif case="0" />
                <if case="1">Bad1!
                <elseif case="1"/>Bad2!
                <else/>Bad3!
                </if>b
            <elseif case="0" />c
                <if case="1">Bad1!
                <elseif case="1" />Bad2!
                <else/>Bad3!
                </if>
            <else />
                <if case="0">Bad1!
                <elseif case="0" />Bad2!
                <elseif case="0" />Bad3!
                </if>d
            </if>)";
    helper.EqualsTrue(String<wchar_t>::Trim(Template::Render(content, value, ss).GetString()) == LR"(d)", "(Render())",
                      __LINE__);
    ss.Clear();
}

static void TestIfLTag2(QTest &helper) {
    StringStream<wchar_t> ss;
    Value<wchar_t>        value;
    const wchar_t        *content;

    value[LR"(name)"] = LR"(Qentem)";

    content = LR"(<if case="1">{var:name})";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(<if case="1">Qentem)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if<if case="1">{var:name}</if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(<ifQentem)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="1"><if case="1">{var:name}</if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(<if case="1">Qentem)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="1"><if case="1"><if case="1">{var:name}</if></if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(<if case="1">Qentem)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="ABC">{var:name}</if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if>{var:name}</if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="0"><elseif />{var:name}</if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<iw case="0">{var:name}</if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(<iw case="0">Qentem</if>)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="0"{var:name}</if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<if case="0"><else {var:name}</if>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();
}

static void TestRenderL1(QTest &helper) {
    constexpr SizeT32 size_4 = (8 * 4);

    StringStream<wchar_t> ss;
    StringStream<wchar_t> content;
    StringStream<wchar_t> output;
    String<wchar_t>       str;
    Value<wchar_t>        value;

    for (SizeT32 i = 0; i < size_4; i++) {
        value += i;
    }

    for (SizeT32 i = 0; i < size_4; i++) {
        content += LR"({var:)";
        str.Reset();
        Digit::NumberToString(str, i);
        content += str;
        output += str;
        content += LR"(})";
    }

    helper.EqualsTrue(Template::Render(content.First(), content.Length(), value, ss) == output, "(Render())", __LINE__);
    ss.Clear();

    content.Clear();
    output.Clear();

    SizeT32 size = 8;
    for (SizeT32 i = 0, x = 1; i < size_4; i++, x++) {
        if (x != size) {
            content += LR"({var:)";
            str.Reset();
            Digit::NumberToString(str, i);
            content += str;
            content += LR"(})";

            output += str;
        } else {
            size += 8;

            content += LR"({math: 1 + )";
            str.Reset();
            Digit::NumberToString(str, i);
            content += str;
            content += LR"(})";

            Digit::NumberToString(output, 1U + i);
        }
    }

    helper.EqualsTrue(Template::Render(content.First(), content.Length(), value, ss) == output, "(Render())", __LINE__);
    ss.Clear();

    content.Clear();
    output.Clear();

    size = 8;
    for (SizeT32 i = 0, x = 1; i < size_4; i++, x++) {
        if (x != size) {
            content += LR"({var:)";
            str.Reset();
            Digit::NumberToString(str, i);
            content += str;
            content += LR"(})";

            output += str;
        } else {
            size += 8;

            content += LR"({if case="{var:)";
            Digit::NumberToString(content, i);
            content += LR"(}<)";
            Digit::NumberToString(content, 1U + i);
            content += LR"(" true="yes"})";

            output += LR"(yes)";
        }
    }

    helper.EqualsTrue(Template::Render(content.First(), content.Length(), value, ss) == output, "(Render())", __LINE__);
    ss.Clear();

    content.Clear();
    output.Clear();

    size = 8;
    for (SizeT32 i = 0, x = 1; i < size_4; i++, x++) {
        if (x != size) {
            content += LR"({var:)";
            str.Reset();
            Digit::NumberToString(str, i);
            content += str;
            content += LR"(})";

            output += str;
        } else {
            size += 8;
            content += LR"(<if case="1">A</if>)";
            output += LR"(A)";
        }
    }

    helper.EqualsTrue(Template::Render(content.First(), content.Length(), value, ss) == output, "(Render())", __LINE__);
    ss.Clear();
}

static void TestRenderL2(QTest &helper) {
    StringStream<wchar_t> ss;
    Value<wchar_t>        value;
    const wchar_t        *content;

    value += 0;
    value += 1;
    value += 2;
    value += 5;
    value += 10;

    content = LR"(<loop value="loop1_val">{var:~loop1_val[0 </loop>)";
    helper.EqualsTrue(
        Template::Render(content, value, ss) ==
            LR"({var:~loop1_val[0 {var:~loop1_val[0 {var:~loop1_val[0 {var:~loop1_val[0 {var:~loop1_val[0 )",
        "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<loop value="loop1_val">{var:loop1_val[]}</loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) ==
                          LR"({var:loop1_val[]}{var:loop1_val[]}{var:loop1_val[]}{var:loop1_val[]}{var:loop1_val[]})",
                      "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<loop set="numbers" value="val_">{var:val_}</loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"()", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<loop value="this_number"><if case="({var:this_number} % 2) == 1">{var:this_number},</if></loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(1,5,)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<loop value="loop1_val">{if case="{var:loop1_val} < 5", true="{var:loop1_val}"}</loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(012)", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<loop value="loop1_val">{if case="{var:loop1_val} < 5", true="{var:4}"}</loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(101010)", "(Render())", __LINE__);
    ss.Clear();

    value = JSON::Parse(LR"([[[1,2,3]]])");

    content = LR"(<loop value="loop1_val">{var:loop1_val[0][2]}</loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"(3)", "(Render())", __LINE__);
    ss.Clear();

    value = Qentem::JSON::Parse(LR"({"abc": [0,10,300], "xyz":[[1],[2],[3]]})");

    content = LR"(<loop set="xyz" value="lvar"> {var:lvar[0]} </loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"( 1  2  3 )", "(Render())", __LINE__);
    ss.Clear();

    content = LR"(<loop set="xyz" value="lvar"><loop set="lvar" value="lvar2"> {math:{var:lvar2}+3} </loop></loop>)";
    helper.EqualsTrue(Template::Render(content, value, ss) == LR"( 4  5  6 )", "(Render())", __LINE__);
    ss.Clear();
}

static int RunTemplateLTests() {
    QTest helper{"Template.hpp (Wide char)", __FILE__};

    helper.PrintGroupName();

    helper.Test("Variable Tag Test 1", TestVariableLTag1);
    helper.Test("Variable Tag Test 2", TestVariableLTag2);
    helper.Test("Variable Tag Test 3", TestVariableLTag3);
    helper.Test("Variable Tag Test 4", TestVariableLTag4);

    helper.Test("Raw Variable Tag Test 1", TestRawVariableLTag1);
    helper.Test("Raw Variable Tag Test 2", TestRawVariableLTag2);
    helper.Test("Raw Variable Tag Test 3", TestRawVariableLTag3);
    helper.Test("Raw Variable Tag Test 4", TestRawVariableLTag4);

    helper.Test("Math Tag Test 1", TestMathLTag1);
    helper.Test("Math Tag Test 2", TestMathLTag2);

    helper.Test("Inline if Tag Test", TestInlineIfLTag);

    helper.Test("Loop Tag Test 1", TestLoopLTag1);
    helper.Test("Loop Tag Test 2", TestLoopLTag2);
    helper.Test("Loop Tag Test 3", TestLoopLTag3);

    helper.Test("If Tag Test 1", TestIfLTag1);
    helper.Test("If Tag Test 2", TestIfLTag2);

    helper.Test("Render Test 1", TestRenderL1);
    helper.Test("Render Test 2", TestRenderL2);

    return helper.EndTests();
}

} // namespace Test
} // namespace Qentem

#endif
