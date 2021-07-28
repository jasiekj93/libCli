/**
 * @file String.test.cpp
 * @author Adrian Szczepanski
 * @date 23-07-2021
 * @brief 
 * @details
 */

#include <libCli/Utils/String.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace Cli::Utils;

static constexpr size_t SIZE = 5;

TEST_GROUP(StringTest)
{

};

TEST(StringTest, FindWord_Nullptr)
{
    auto span = String::FindWord(nullptr);

    CHECK(nullptr == span.data);
    CHECK_EQUAL(0, span.size);
}

TEST(StringTest, OnlySpaces)
{
    const char text[] = { ' ', '\t', '\v', '\n', '\r', '\0' };
    auto span = String::FindWord(text);

    CHECK(nullptr == span.data);
    CHECK_EQUAL(0, span.size);
}

TEST(StringTest, OnlySpaces)
{
    const char text[] = { ' ', '\t', '\v', '\n', '\r', '\0' };
    auto span = String::FindWord(text);

    CHECK(nullptr == span.data);
    CHECK_EQUAL(0, span.size);
}