/**
 * @file CommandTemplateBuffer.test.cpp
 * @author Adrian Szczepanski
 * @date 29-07-2021
 * @brief 
 * @details
 */

#include <libCli/Utils/CommandTemplateBuffer.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace Cli;
using namespace Cli::Utils;

TEST_GROUP(CommandTemplateBufferTest)
{

};

TEST(CommandTemplateBufferTest, AddOne)
{
    CommandTemplateBuffer buffer;
    CommandTemplate command("name");

    CHECK(buffer.Put(command))
    CHECK(buffer.Contains("name"));
    CHECK_EQUAL(0, buffer.At("name"));
    CHECK(command == buffer.Get("name"));
}

TEST(CommandTemplateBufferTest, AddTheSame)
{
    CommandTemplateBuffer buffer;
    CommandTemplate command("name", "55");

    CHECK(buffer.Put(command));
    CHECK_FALSE(buffer.Put(command));
    CHECK_EQUAL(1, buffer.Count());
}

TEST(CommandTemplateBufferTest, NotExisting)
{
    CommandTemplateBuffer buffer;
    CommandTemplate command("name", "55");
    buffer.Put(command);

    CHECK_FALSE(buffer.Contains("amen"));
    CHECK_EQUAL(-1, buffer.At("amen"));
    CHECK(CommandTemplate() == buffer.Get("amen"));
}