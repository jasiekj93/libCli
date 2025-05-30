/**
 * @file CommandHelper.test.cpp
 * @author Adrian Szczepanski
 * @date 02-08-2021
 * @brief 
 * @details
 */

#include <libcli/internal/CommandHelper.hpp>
#include <tests/mock/Output.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace cli;
using namespace cli::internal;


TEST_GROUP(CommandHelperTest)
{

};

TEST(CommandHelperTest, OnlyName)
{
    const char expected[] = "zastosowanie: hello\r\n";

    templates::Command command("hello");

    mock::Output output;
    CommandHelper helper(output);

    helper.DisplayHelp(command);

    STRCMP_EQUAL(expected, output.buffer.Data());
}

TEST(CommandHelperTest, NameWithHelp)
{
    const char expected[] = "zastosowanie: hello\r\n"
                            "\tThis is help\r\n";

    templates::Command command("hello", "This is help");

    mock::Output output;
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

    templates::Command command("hello", "This is help", {
        { 'a', model::Argument::Type::Decimal, true, "This is number" }
    });

    mock::Output output;
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

    templates::Command command("hello", "This is help", {
        { 'a', model::Argument::Type::Decimal, false, "This is number" }
    });

    mock::Output output;
    CommandHelper helper(output);

    helper.DisplayHelp(command);

    STRCMP_EQUAL(expected, output.buffer.Data());
}

TEST(CommandHelperTest, OneArgument_NoCommandHelp)
{
    const char expected[] = "zastosowanie: hello -a \r\n"
                            "\r\n"
                            "-a\tcalkowity\tThis is number\r\n";

    templates::Command command("hello", {
        { 'a', model::Argument::Type::Decimal, true, "This is number" }
    });

    mock::Output output;
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

    templates::Command command("hello", "This is help", {
        { 'a', model::Argument::Type::Decimal, false, "This is number" },
        { 'b', model::Argument::Type::Double, true, "This is double" },
        { 'c', model::Argument::Type::Empty, false, "This is empty" },
        { 'd', model::Argument::Type::Hex, true, "This is hex" },
        { 'e', model::Argument::Type::String, true, "This is string" },
    });

    mock::Output output;
    CommandHelper helper(output);

    helper.DisplayHelp(command);

    STRCMP_EQUAL(expected, output.buffer.Data());
}