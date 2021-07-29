/**
 * @file CommandTemplate.test.cpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

#include <libCli/CommandTemplate.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace Cli;


TEST_GROUP(CommandTemplateTest)
{

};

TEST(CommandTemplateTest, DefaultConstructor)
{
    CommandTemplate command;

    CHECK_EQUAL(0, std::strlen(command.Name()));
    CHECK_EQUAL(0, command.Arguments().Count());
}

TEST(CommandTemplateTest, NameConstructor)
{
    CommandTemplate command("hello");

    STRCMP_EQUAL("hello", command.Name());
    CHECK_EQUAL(0, command.Arguments().Count());
}

TEST(CommandTemplateTest, NameConstructor_Nullptr)
{
    CommandTemplate command(nullptr);

    CHECK_EQUAL(0, std::strlen(command.Name()));
    CHECK_EQUAL(0, command.Arguments().Count());
}

TEST(CommandTemplateTest, NameConstructor_TooLong)
{
    CommandTemplate command("ThisIsAVeryVeryLongNameProbablyToLong");

    CHECK_EQUAL(0, std::strlen(command.Name()));
    CHECK_EQUAL(0, command.Arguments().Count());
}

TEST(CommandTemplateTest, NameConstructor_Help)
{
    CommandTemplate command("hello", "help");

    STRCMP_EQUAL("hello", command.Name());
    STRCMP_EQUAL("help", command.Help());
    CHECK_EQUAL(0, command.Arguments().Count());
}

TEST(CommandTemplateTest, NameConstructor_Help_TooLong)
{
    CommandTemplate command("hello", "This Is A Very Very Long Name Probably To Long Very Very Long Help Should Be Shorter");

    CHECK_EQUAL(0, std::strlen(command.Name()));
    CHECK_EQUAL(0, std::strlen(command.Help()));
    CHECK_EQUAL(0, command.Arguments().Count());
}

TEST(CommandTemplateTest, InitalizerListConstructor)
{
    CommandTemplate command("hello", { { 'a', Argument::Type::Double, true }, {'b', Argument::Type::Hex, false } });

    STRCMP_EQUAL("hello", command.Name());
    CHECK_EQUAL(2, command.Arguments().Count());
}

TEST(CommandTemplateTest, InitalizerListConstructor_InvalidName)
{
    CommandTemplate command(nullptr, { { 'a', Argument::Type::Double, true }, {'b', Argument::Type::Hex, false } });

    CHECK_EQUAL(0, std::strlen(command.Name()));
    CHECK_EQUAL(0, command.Arguments().Count());
}