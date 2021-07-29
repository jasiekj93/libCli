/**
 * @file ArgumentTemplate.test.cpp
 * @author Adrian Szczepanski
 * @date 28-07-2021
 * @brief 
 * @details
 */

#include <libCli/ArgumentTemplate.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace Cli;


TEST_GROUP(ArgumentTemplateTest)
{
};

TEST(ArgumentTemplateTest, DefaultConstuctor)
{
    ArgumentTemplate arg;

    CHECK_EQUAL(Argument::INVALID_NAME, arg.Name());
    CHECK(Argument::Type::Empty == arg.Type());
    CHECK_FALSE(arg.IsMandatory());
    STRCMP_EQUAL("", arg.Help());
}

TEST(ArgumentTemplateTest, WithoutHelp)
{
    char name = 'a';
    Argument::Type type = Argument::Type::Double;
    bool isMandatory = true;


    ArgumentTemplate arg(name, type, isMandatory);

    CHECK_EQUAL(name, arg.Name());
    CHECK(type == arg.Type());
    CHECK(arg.IsMandatory());
    STRCMP_EQUAL("", arg.Help());
}

TEST(ArgumentTemplateTest, WithHelp)
{
    char name = 'a';
    Argument::Type type = Argument::Type::Double;
    bool isMandatory = true;
    const char help[] = "This is help";

    ArgumentTemplate arg(name, type, isMandatory, help);

    CHECK_EQUAL(name, arg.Name());
    CHECK(type == arg.Type());
    CHECK(arg.IsMandatory());
    STRCMP_EQUAL(help, arg.Help());
}

TEST(ArgumentTemplateTest, WithHelp_TooLong)
{
    char name = 'a';
    Argument::Type type = Argument::Type::Double;
    bool isMandatory = true;
    const char help[] = "This is too long help to be supported by this library";

    ArgumentTemplate arg(name, type, isMandatory, help);

    CHECK_EQUAL(Argument::INVALID_NAME, arg.Name());
    CHECK(Argument::Type::Empty == arg.Type());
    CHECK_FALSE(arg.IsMandatory());
    STRCMP_EQUAL("", arg.Help());
}