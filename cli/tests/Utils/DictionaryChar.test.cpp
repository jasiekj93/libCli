/**
 * @file DictionaryChar.test.cpp
 * @author Adrian Szczepanski
 * @date 29-07-2021
 * @brief 
 * @details
 */

#include <libcli/Utils/DictionaryChar.hpp>
#include <libcli/Model/Argument.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace cli;
using namespace cli::Utils;

static constexpr size_t SIZE = 5;

TEST_GROUP(DictionaryCharTest)
{

};

TEST(DictionaryCharTest, AddOne)
{
    DictionaryChar<Model::Argument, SIZE> buffer;
    Model::Argument arg('a', "55");

    CHECK(buffer.Put(arg))
    CHECK(buffer.Contains('a'));
    CHECK_EQUAL(0, buffer.At('a'));
    CHECK(arg == buffer.Get('a'));
}

TEST(DictionaryCharTest, AddTheSame)
{
    DictionaryChar<Model::Argument, SIZE> buffer;
    Model::Argument arg('a', "55");

    CHECK(buffer.Put(arg));
    CHECK_FALSE(buffer.Put(arg));
    CHECK_EQUAL(1, buffer.Count());
}

TEST(DictionaryCharTest, NotExisting)
{
    DictionaryChar<Model::Argument, SIZE> buffer;
    Model::Argument arg('a', "55");
    buffer.Put(arg);

    CHECK_FALSE(buffer.Contains('b'));
    CHECK_EQUAL(-1, buffer.At('b'));
    CHECK(Model::Argument() == buffer.Get('b'));
}