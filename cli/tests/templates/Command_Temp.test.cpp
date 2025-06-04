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

    CHECK_EQUAL(0, std::strlen(command.Name()));
    CHECK(command.Arguments().empty());
}

TEST(CommandTempTest, NameConstructor)
{
    Command command("hello");

    STRCMP_EQUAL("hello", command.Name());
    CHECK(command.Arguments().empty());
}

TEST(CommandTempTest, NameConstructor_Nullptr)
{
    Command command(nullptr);

    CHECK_EQUAL(0, std::strlen(command.Name()));
    CHECK(command.Arguments().empty());
}

TEST(CommandTempTest, NameConstructor_TooLong)
{
    Command command("ThisIsAVeryVeryLongNameProbablyToLong");

    CHECK_EQUAL(0, std::strlen(command.Name()));
    CHECK(command.Arguments().empty());
}

TEST(CommandTempTest, NameConstructor_Help)
{
    Command command("hello", "help");

    STRCMP_EQUAL("hello", command.Name());
    STRCMP_EQUAL("help", command.Help());
    CHECK(command.Arguments().empty());
}

TEST(CommandTempTest, NameConstructor_Help_TooLong)
{
    Command command("hello", "This Is A Very Very Long Name Probably To Long Very Very Long Help Should Be Shorter");

    CHECK_EQUAL(0, std::strlen(command.Name()));
    CHECK_EQUAL(0, std::strlen(command.Help()));
    CHECK(command.Arguments().empty());
}

TEST(CommandTempTest, InitalizerListConstructor)
{
    Command command("hello", { { 'a', model::Argument::Type::DOUBLE, true }, {'b', model::Argument::Type::HEX, false } });

    STRCMP_EQUAL("hello", command.Name());
    CHECK_EQUAL(2, command.Arguments().size());
}

TEST(CommandTempTest, InitalizerListConstructor_InvalidName)
{
    Command command(nullptr, { { 'a', model::Argument::Type::DOUBLE, true }, {'b', model::Argument::Type::HEX, false } });

    CHECK_EQUAL(0, std::strlen(command.Name()));
    CHECK(command.Arguments().empty());
}