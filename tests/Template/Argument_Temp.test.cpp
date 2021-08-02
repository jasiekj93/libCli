/**
 * @file Argument_Temp.test.cpp
 * @author Adrian Szczepanski
 * @date 28-07-2021
 * @brief 
 * @details
 */

#include <libCli/Template/Argument.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace Cli;
using namespace Cli::Template;

TEST_GROUP(ArgumentTempTest)
{
};

TEST(ArgumentTempTest, DefaultConstuctor)
{
    Argument arg;

    CHECK_EQUAL(Model::Argument::INVALID_NAME, arg.Name());
    CHECK(Model::Argument::Type::Empty == arg.GetType());
    CHECK_FALSE(arg.IsMandatory());
    STRCMP_EQUAL("", arg.Help());
}

TEST(ArgumentTempTest, WithoutHelp)
{
    char name = 'a';
    Model::Argument::Type type = Model::Argument::Type::Double;
    bool isMandatory = true;


    Argument arg(name, type, isMandatory);

    CHECK_EQUAL(name, arg.Name());
    CHECK(type == arg.GetType());
    CHECK(arg.IsMandatory());
    STRCMP_EQUAL("", arg.Help());
}

TEST(ArgumentTempTest, WithHelp)
{
    char name = 'a';
    Model::Argument::Type type = Model::Argument::Type::Double;
    bool isMandatory = true;
    const char help[] = "This is help";

    Argument arg(name, type, isMandatory, help);

    CHECK_EQUAL(name, arg.Name());
    CHECK(type == arg.GetType());
    CHECK(arg.IsMandatory());
    STRCMP_EQUAL(help, arg.Help());
}

TEST(ArgumentTempTest, WithHelp_TooLong)
{
    char name = 'a';
    Model::Argument::Type type = Model::Argument::Type::Double;
    bool isMandatory = true;
    const char help[] = "This is too long help to be supported by this library";

    Argument arg(name, type, isMandatory, help);

    CHECK_EQUAL(Model::Argument::INVALID_NAME, arg.Name());
    CHECK(Model::Argument::Type::Empty == arg.GetType());
    CHECK_FALSE(arg.IsMandatory());
    STRCMP_EQUAL("", arg.Help());
}