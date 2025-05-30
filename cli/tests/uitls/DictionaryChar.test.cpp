/**
 * @file DictionaryChar.test.cpp
 * @author Adrian Szczepanski
 * @date 29-07-2021
 * @brief 
 * @details
 */

#include <libcli/utils/DictionaryChar.hpp>
#include <libcli/model/Argument.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace cli;
using namespace cli::utils;

static constexpr size_t SIZE = 5;

TEST_GROUP(DictionaryCharTest)
{

};

TEST(DictionaryCharTest, AddOne)
{
    DictionaryChar<model::Argument, SIZE> buffer;
    model::Argument arg('a', "55");

    CHECK(buffer.Put(arg))
    CHECK(buffer.Contains('a'));
    CHECK_EQUAL(0, buffer.At('a'));
    CHECK(arg == buffer.Get('a'));
}

TEST(DictionaryCharTest, AddTheSame)
{
    DictionaryChar<model::Argument, SIZE> buffer;
    model::Argument arg('a', "55");

    CHECK(buffer.Put(arg));
    CHECK_FALSE(buffer.Put(arg));
    CHECK_EQUAL(1, buffer.Count());
}

TEST(DictionaryCharTest, NotExisting)
{
    DictionaryChar<model::Argument, SIZE> buffer;
    model::Argument arg('a', "55");
    buffer.Put(arg);

    CHECK_FALSE(buffer.Contains('b'));
    CHECK_EQUAL(-1, buffer.At('b'));
    CHECK(model::Argument() == buffer.Get('b'));
}