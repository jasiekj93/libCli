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

    CHECK(model::Argument::Type::EMPTY == arg.getType());
    CHECK_FALSE(arg.isMandatory());
    STRCMP_EQUAL("", arg.getHelp().data());
}

TEST(ArgumentTempTest, WithoutHelp)
{
    model::Argument::Type type = model::Argument::Type::DOUBLE;
    bool isMandatory = true;

    Argument arg(type, isMandatory);

    CHECK(type == arg.getType());
    CHECK(arg.isMandatory());
    STRCMP_EQUAL("", arg.getHelp().data());
}

TEST(ArgumentTempTest, WithHelp)
{
    model::Argument::Type type = model::Argument::Type::DOUBLE;
    bool isMandatory = true;
    const char help[] = "This is help";

    Argument arg(type, isMandatory, help);

    CHECK(type == arg.getType());
    CHECK(arg.isMandatory());
    STRCMP_EQUAL(help, arg.getHelp().data());
}

// TEST(ArgumentTempTest, WithHelp_TooLong)
// {
//     model::Argument::Type type = model::Argument::Type::DOUBLE;
//     bool isMandatory = true;
//     const char help[] = "This is too long help to be supported by this library";

//     Argument arg(type, isMandatory, help);

//     CHECK(model::Argument::Type::DOUBLE == arg.getType());
//     CHECK(arg.isMandatory());
//     STRCMP_EQUAL("", arg.getHelp().data());
// }