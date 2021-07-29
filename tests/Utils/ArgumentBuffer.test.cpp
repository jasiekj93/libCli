/**
 * @file ArgumentBuffer.test.cpp
 * @author Adrian Szczepanski
 * @date 29-07-2021
 * @brief 
 * @details
 */

#include <libCli/Utils/ArgumentBuffer.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace Cli;
using namespace Cli::Utils;

TEST_GROUP(ArgumentBufferTest)
{

};

TEST(ArgumentBufferTest, AddOne)
{
    ArgumentBuffer buffer;
    Argument arg('a', "55");

    CHECK(buffer.Put(arg))
    CHECK(buffer.Contains('a'));
    CHECK_EQUAL(0, buffer.At('a'));
    CHECK(arg == buffer.Get('a'));
}

TEST(ArgumentBufferTest, AddTheSame)
{
    ArgumentBuffer buffer;
    Argument arg('a', "55");

    CHECK(buffer.Put(arg));
    CHECK_FALSE(buffer.Put(arg));
    CHECK_EQUAL(1, buffer.Count());
}

TEST(ArgumentBufferTest, NotExisting)
{
    ArgumentBuffer buffer;
    Argument arg('a', "55");
    buffer.Put(arg);

    CHECK_FALSE(buffer.Contains('b'));
    CHECK_EQUAL(-1, buffer.At('b'));
    CHECK(Argument() == buffer.Get('b'));
}