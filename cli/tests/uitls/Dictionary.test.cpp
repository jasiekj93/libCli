/**
 * @file Dictionary.test.cpp
 * @author Adrian Szczepanski
 * @date 29-07-2021
 * @brief 
 * @details
 */

#include <libcli/utils/Dictionary.hpp>
#include <libcli/templates/Command.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace cli;
using namespace cli::utils;

static constexpr size_t SIZE = 5;

TEST_GROUP(DictionaryTest)
{

};

TEST(DictionaryTest, AddOne)
{
    Dictionary<templates::Command, SIZE> buffer;
    templates::Command command("name");

    CHECK(buffer.Put(command))
    CHECK(buffer.Contains("name"));
    CHECK_EQUAL(0, buffer.At("name"));
    CHECK(command == buffer.Get("name"));
}

TEST(DictionaryTest, AddTheSame)
{
    Dictionary<templates::Command, SIZE> buffer;
    templates::Command command("name", "55");

    CHECK(buffer.Put(command));
    CHECK_FALSE(buffer.Put(command));
    CHECK_EQUAL(1, buffer.Count());
}

TEST(DictionaryTest, NotExisting)
{
    Dictionary<templates::Command, SIZE> buffer;
    templates::Command command("name", "55");
    buffer.Put(command);

    CHECK_FALSE(buffer.Contains("amen"));
    CHECK_EQUAL(-1, buffer.At("amen"));
    CHECK(templates::Command() == buffer.Get("amen"));
}