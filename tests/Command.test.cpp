/**
 * @file Command.test.cpp
 * @author Adrian Szczepanski
 * @date 28-07-2021
 * @brief 
 * @details
 */

#include <libCli/Command.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace Cli;


TEST_GROUP(CommandTest)
{

};


TEST(CommandTest, EmptyString)
{
    Command command;

    CHECK(command.IsNull());
    CHECK(nullptr == command.GetName());
    CHECK_EQUAL(0, command.ArgumentCount());
}


TEST(CommandTest, OnlyName)
{   
    const char text[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(text, command.GetName());
    CHECK_EQUAL(0, command.ArgumentCount());
}

TEST(CommandTest, OnlyName_SpacesAtBeginning)
{   
    const char text[] = "   hello";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK_EQUAL(0, command.ArgumentCount());
}

TEST(CommandTest, TwoWords_NotAnArgument)
{
    const char text[] = "hello world";

    Command command(text);

    CHECK(command.IsNull());
    CHECK(nullptr == command.GetName());
    CHECK_EQUAL(0, command.ArgumentCount());
}

// TEST(CommandTest, OneArgument)
// {
//     const char text[] = "hello -a arg";
//     const char expectedName[] = "hello";

//     Command command(text);

//     CHECK_FALSE(command.IsNull());
//     STRCMP_EQUAL(expectedName, command.GetName());
//     CHECK_EQUAL(1, command.ArgumentCount());
//     CHECK_EQUAL(1, command.ArgumentCount());
// }

