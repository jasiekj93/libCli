/**
 * @file Dictionary.test.cpp
 * @author Adrian Szczepanski
 * @date 29-07-2021
 * @brief 
 * @details
 */

#include <libcli/Utils/Dictionary.hpp>
#include <libcli/Template/Command.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace cli;
using namespace cli::Utils;

static constexpr size_t SIZE = 5;

TEST_GROUP(DictionaryTest)
{

};

TEST(DictionaryTest, AddOne)
{
    Dictionary<Template::Command, SIZE> buffer;
    Template::Command command("name");

    CHECK(buffer.Put(command))
    CHECK(buffer.Contains("name"));
    CHECK_EQUAL(0, buffer.At("name"));
    CHECK(command == buffer.Get("name"));
}

TEST(DictionaryTest, AddTheSame)
{
    Dictionary<Template::Command, SIZE> buffer;
    Template::Command command("name", "55");

    CHECK(buffer.Put(command));
    CHECK_FALSE(buffer.Put(command));
    CHECK_EQUAL(1, buffer.Count());
}

TEST(DictionaryTest, NotExisting)
{
    Dictionary<Template::Command, SIZE> buffer;
    Template::Command command("name", "55");
    buffer.Put(command);

    CHECK_FALSE(buffer.Contains("amen"));
    CHECK_EQUAL(-1, buffer.At("amen"));
    CHECK(Template::Command() == buffer.Get("amen"));
}