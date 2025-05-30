/**
 * @file CommandHelper.test.cpp
 * @author Adrian Szczepanski
 * @date 02-08-2021
 * @brief 
 * @details
 */

#include <libcli/Internal/CommandHelper.hpp>
#include <tests/Mock/Output.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace cli;
using namespace cli::Internal;


TEST_GROUP(CommandHelperTest)
{

};

TEST(CommandHelperTest, OnlyName)
{
    const char expected[] = "zastosowanie: hello\r\n";

    Template::Command command("hello");

    Mock::Output output;
    CommandHelper helper(output);

    helper.DisplayHelp(command);

    STRCMP_EQUAL(expected, output.buffer.Data());
}

TEST(CommandHelperTest, NameWithHelp)
{
    const char expected[] = "zastosowanie: hello\r\n"
                            "\tThis is help\r\n";

    Template::Command command("hello", "This is help");

    Mock::Output output;
    CommandHelper helper(output);

    helper.DisplayHelp(command);

    STRCMP_EQUAL(expected, output.buffer.Data());
}

TEST(CommandHelperTest, OneArgument_Mandatory)
{
    const char expected[] = "zastosowanie: hello -a \r\n"
                            "\tThis is help\r\n"
                            "\r\n"
                            "-a\tcalkowity\tThis is number\r\n";

    Template::Command command("hello", "This is help", {
        { 'a', Model::Argument::Type::Decimal, true, "This is number" }
    });

    Mock::Output output;
    CommandHelper helper(output);

    helper.DisplayHelp(command);

    STRCMP_EQUAL(expected, output.buffer.Data());
}

TEST(CommandHelperTest, OneArgument_Optional)
{
    const char expected[] = "zastosowanie: hello [-a] \r\n"
                            "\tThis is help\r\n"
                            "\r\n"
                            "-a\tcalkowity\tThis is number\r\n";

    Template::Command command("hello", "This is help", {
        { 'a', Model::Argument::Type::Decimal, false, "This is number" }
    });

    Mock::Output output;
    CommandHelper helper(output);

    helper.DisplayHelp(command);

    STRCMP_EQUAL(expected, output.buffer.Data());
}

TEST(CommandHelperTest, OneArgument_NoCommandHelp)
{
    const char expected[] = "zastosowanie: hello -a \r\n"
                            "\r\n"
                            "-a\tcalkowity\tThis is number\r\n";

    Template::Command command("hello", {
        { 'a', Model::Argument::Type::Decimal, true, "This is number" }
    });

    Mock::Output output;
    CommandHelper helper(output);

    helper.DisplayHelp(command);

    STRCMP_EQUAL(expected, output.buffer.Data());
}

TEST(CommandHelperTest, ManyArguments)
{
    const char expected[] = "zastosowanie: hello [-a] -b [-c] -d -e \r\n"
                            "\tThis is help\r\n"
                            "\r\n"
                            "-a\tcalkowity\tThis is number\r\n"
                            "-b\tzmiennoprzecinkowy\tThis is double\r\n"
                            "-c\t \tThis is empty\r\n"
                            "-d\tszesnastkowy\tThis is hex\r\n"
                            "-e\tciag znakow\tThis is string\r\n";

    Template::Command command("hello", "This is help", {
        { 'a', Model::Argument::Type::Decimal, false, "This is number" },
        { 'b', Model::Argument::Type::Double, true, "This is double" },
        { 'c', Model::Argument::Type::Empty, false, "This is empty" },
        { 'd', Model::Argument::Type::Hex, true, "This is hex" },
        { 'e', Model::Argument::Type::String, true, "This is string" },
    });

    Mock::Output output;
    CommandHelper helper(output);

    helper.DisplayHelp(command);

    STRCMP_EQUAL(expected, output.buffer.Data());
}