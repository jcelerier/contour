/**
 * This file is part of the "libterminal" project
 *   Copyright (c) 2019-2020 Christian Parpart <christian@parpart.family>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <crispy/utils.h>
#include <catch2/catch.hpp>

using namespace std::string_view_literals;

TEST_CASE("utils.split.0")
{
    auto result = crispy::splitKeyValuePairs("", ':');
    CHECK(result.size() == 0);
}

TEST_CASE("utils.split.1")
{
    auto result = crispy::splitKeyValuePairs("foo=bar", ':');
    CHECK(result.size() == 1);
    CHECK(result["foo"] == "bar");

    auto result2 = crispy::splitKeyValuePairs("foo=bar::", ':');
    CHECK(result2.size() == 1);
    CHECK(result2["foo"] == "bar");

    auto result3 = crispy::splitKeyValuePairs("::foo=bar", ':');
    CHECK(result3.size() == 1);
    CHECK(result3["foo"] == "bar");
}

TEST_CASE("utils.split.2")
{
    auto result = crispy::splitKeyValuePairs("foo=bar:fnord=tar", ':');
    CHECK(result.size() == 2);
    CHECK(result["foo"] == "bar");
    CHECK(result["fnord"] == "tar");

    auto result2 = crispy::splitKeyValuePairs("foo=bar::fnord=tar", ':');
    CHECK(result2["foo"] == "bar");
    CHECK(result2["fnord"] == "tar");
    CHECK(result2.size() == 2);
}

template<typename R, typename... A> R ret(R(*)(A...));
template<typename C, typename R, typename... A> R ret(R(C::*)(A...));

TEST_CASE("utils.to_integer.integer_type")
{
    static_assert(std::is_same_v<
            uint8_t,
            std::remove_reference_t<decltype(*crispy::to_integer<10, uint8_t>(""sv))>
    >);

    static_assert(std::is_same_v<
            int,
            std::remove_reference_t<decltype(*crispy::to_integer<10, int>(""sv))>
    >);

    static_assert(std::is_same_v<
            unsigned,
            std::remove_reference_t<decltype(*crispy::to_integer<10, unsigned>(""sv))>
    >);

    static_assert(std::is_same_v<
            uint64_t,
            std::remove_reference_t<decltype(*crispy::to_integer<10, uint64_t>(""sv))>
    >);
}

TEST_CASE("utils.to_integer.bad")
{
    CHECK(crispy::to_integer<10>(""sv).has_value() == false);
    CHECK(crispy::to_integer<10>("bad"sv).has_value() == false);
}

TEST_CASE("utils.to_integer.2")
{
    CHECK(crispy::to_integer<2>("0"sv).value_or(-1) == 0);
    CHECK(crispy::to_integer<2>("10"sv).value_or(-1) == 0b10);
    CHECK(crispy::to_integer<2>("1100101"sv).value_or(-1) == 0b1100101);
}

TEST_CASE("utils.to_integer.10")
{
    CHECK(crispy::to_integer<10>("0"sv).value_or(-1) == 0);
    CHECK(crispy::to_integer<10>("9"sv).value_or(-1) == 9);
    CHECK(crispy::to_integer<10>("18"sv).value_or(-1) == 18);
    CHECK(crispy::to_integer<10>("321"sv).value_or(-1) == 321);
    CHECK(crispy::to_integer<10>("12345"sv).value_or(-1) == 12345);

    // defaulted base is base-10
    CHECK(crispy::to_integer("12345"sv).value_or(-1) == 12345);
}

TEST_CASE("utils.to_integer.16")
{
    // upper case hex digits
    CHECK(crispy::to_integer<16>("B"sv).value_or(-1) == 0x0B);
    CHECK(crispy::to_integer<16>("0B"sv).value_or(-1) == 0x0B);
    CHECK(crispy::to_integer<16>("B0"sv).value_or(-1) == 0xB0);
    CHECK(crispy::to_integer<16>("B0"sv).value_or(-1) == 0xB0);
    CHECK(crispy::to_integer<16>("ABCDEF"sv).value_or(-1) == 0xABCDEF);

    // lower case hex digits
    CHECK(crispy::to_integer<16>("b"sv).value_or(-1) == 0x0B);
    CHECK(crispy::to_integer<16>("0b"sv).value_or(-1) == 0x0B);
    CHECK(crispy::to_integer<16>("b0"sv).value_or(-1) == 0xB0);
    CHECK(crispy::to_integer<16>("b0"sv).value_or(-1) == 0xB0);
    CHECK(crispy::to_integer<16>("abcdef"sv).value_or(-1) == 0xABCDEF);

    CHECK(crispy::to_integer<16>("0"sv).value_or(-1) == 0x0);
    CHECK(crispy::to_integer<16>("9"sv).value_or(-1) == 0x9);
    CHECK(crispy::to_integer<16>("18"sv).value_or(-1) == 0x18);
    CHECK(crispy::to_integer<16>("321"sv).value_or(-1) == 0x321);
    CHECK(crispy::to_integer<16>("12345"sv).value_or(-1) == 0x12345);
}

TEST_CASE("fromHexString")
{
    CHECK(!crispy::fromHexString("abc"sv));
    CHECK(!crispy::fromHexString("GX"sv));

    CHECK(crispy::fromHexString(""sv).value() == ""sv);
    CHECK(crispy::fromHexString("61"sv).value() == "a"sv);
    CHECK(crispy::fromHexString("4162"sv).value() == "Ab"sv);
}
