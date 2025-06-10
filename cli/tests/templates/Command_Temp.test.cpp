/**
 * @file Command_Temp.test.cpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

#include <libcli/templates/Command.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace cli;
using namespace cli::templates;


TEST_GROUP(CommandTempTest)
{

};

TEST(CommandTempTest, DefaultConstructor)
{
    Command command;

    CHECK(command.getName().empty());
    CHECK(command.getArguments().empty());
}

TEST(CommandTempTest, NameConstructor)
{
    Command command("hello");

    STRCMP_EQUAL("hello", command.getName().data());
    CHECK(command.getArguments().empty());
}

TEST(CommandTempTest, NameConstructor_Nullptr)
{
    Command command(nullptr);

    CHECK(command.getName().empty());
    CHECK(command.getArguments().empty());
}

// TEST(CommandTempTest, NameConstructor_TooLong)
// {
//     Command command("ThisIsAVeryVeryLongNameProbablyToLong");

//     CHECK(command.getName().empty());
//     CHECK(command.getArguments().empty());
// }

TEST(CommandTempTest, NameConstructor_Help)
{
    Command command("hello", "help");

    STRCMP_EQUAL("hello", command.getName().data());
    STRCMP_EQUAL("help", command.getHelp().data());
    CHECK(command.getArguments().empty());
}

// TEST(CommandTempTest, NameConstructor_Help_TooLong)
// {
//     Command command("hello", "This Is A Very Very Long Name Probably To Long Very Very Long Help Should Be Shorter");

//     CHECK(command.getName().empty());
//     CHECK(command.getHelp().empty());
//     CHECK(command.getArguments().empty());
// }

TEST(CommandTempTest, InitalizerListConstructor)
{
    Command command("hello", { 
        { 'a', { model::Argument::Type::DOUBLE, true }}, 
        { 'b', { model::Argument::Type::HEX, false } } 
    });

    STRCMP_EQUAL("hello", command.getName().data());
    CHECK_EQUAL(2, command.getArguments().size());
}

TEST(CommandTempTest, InitalizerListConstructor_InvalidName)
{
    Command command("", { 
        { 'a', { model::Argument::Type::DOUBLE, true }}, 
        {'b', { model::Argument::Type::HEX, false } } 
    });

    CHECK(command.getName().empty());
    CHECK(command.getArguments().empty());
}