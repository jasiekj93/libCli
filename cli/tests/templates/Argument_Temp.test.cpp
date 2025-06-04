/**
 * @file Argument_Temp.test.cpp
 * @author Adrian Szczepanski
 * @date 28-07-2021
 * @brief 
 * @details
 */

#include <libcli/templates/Argument.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace cli;
using namespace cli::templates;

TEST_GROUP(ArgumentTempTest)
{
};

TEST(ArgumentTempTest, DefaultConstuctor)
{
    Argument arg;

    CHECK_EQUAL(model::Argument::INVALID_NAME, arg.getName());
    CHECK(model::Argument::Type::EMPTY == arg.getType());
    CHECK_FALSE(arg.isMandatory());
    STRCMP_EQUAL("", arg.help());
}

TEST(ArgumentTempTest, WithoutHelp)
{
    char name = 'a';
    model::Argument::Type type = model::Argument::Type::DOUBLE;
    bool isMandatory = true;


    Argument arg(name, type, isMandatory);

    CHECK_EQUAL(name, arg.getName());
    CHECK(type == arg.getType());
    CHECK(arg.isMandatory());
    STRCMP_EQUAL("", arg.help());
}

TEST(ArgumentTempTest, WithHelp)
{
    char name = 'a';
    model::Argument::Type type = model::Argument::Type::DOUBLE;
    bool isMandatory = true;
    const char help[] = "This is help";

    Argument arg(name, type, isMandatory, help);

    CHECK_EQUAL(name, arg.getName());
    CHECK(type == arg.getType());
    CHECK(arg.isMandatory());
    STRCMP_EQUAL(help, arg.help());
}

TEST(ArgumentTempTest, WithHelp_TooLong)
{
    char name = 'a';
    model::Argument::Type type = model::Argument::Type::DOUBLE;
    bool isMandatory = true;
    const char help[] = "This is too long help to be supported by this library";

    Argument arg(name, type, isMandatory, help);

    CHECK_EQUAL(model::Argument::INVALID_NAME, arg.getName());
    CHECK(model::Argument::Type::EMPTY == arg.getType());
    CHECK_FALSE(arg.isMandatory());
    STRCMP_EQUAL("", arg.help());
}