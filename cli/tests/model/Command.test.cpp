/**
 * @file Command.test.cpp
 * @author Adrian Szczepanski
 * @date 28-07-2021
 * @brief 
 * @details
 */

#include <libcli/model/Command.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace cli;
using namespace cli::model;

TEST_GROUP(CommandTest)
{

};


TEST(CommandTest, EmptyString)
{
    Command command;

    CHECK(command.IsNull());
    CHECK(nullptr == command.GetName());
    CHECK(command.Arguments().empty());
}


TEST(CommandTest, OnlyName)
{   
    const char text[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(text, command.GetName());
    CHECK(command.Arguments().empty());
}

TEST(CommandTest, TooLongNameName)
{   
    const char text[] = "helloThisIsVeryLongCommandTooBigToBeHandledByThisLibrary";

    Command command(text);

    CHECK(command.IsNull());
    CHECK(nullptr == command.GetName());
    CHECK(command.Arguments().empty());
}

TEST(CommandTest, OnlyName_SpacesAtBeginning)
{   
    const char text[] = "   hello";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK(command.Arguments().empty());
}

TEST(CommandTest, TwoWords_NotAnArgument)
{
    const char text[] = "hello world";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK(command.Arguments().empty());
}

TEST(CommandTest, OneArgument)
{
    const char text[] = "hello -a arg";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK_EQUAL(1, command.Arguments().size());

    CHECK(command.Arguments().contains('a'));
    CHECK(Argument::Type::STRING == command.Arguments().at('a').getType());
    STRCMP_EQUAL("arg", command.Arguments().at('a').asString().data());
}

TEST(CommandTest, OneArgument_MoreSpaces)
{
    const char text[] = "    hello     -a     arg    ";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK_EQUAL(1, command.Arguments().size());

    CHECK(command.Arguments().contains('a'));
    CHECK(Argument::Type::STRING == command.Arguments().at('a').getType());
    STRCMP_EQUAL("arg", command.Arguments().at('a').asString().data());
}

TEST(CommandTest, OneArgument_NoSpace)
{
    const char text[] = "hello -aarg";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK_EQUAL(1, command.Arguments().size());

    CHECK(command.Arguments().contains('a'));
    CHECK(Argument::Type::STRING == command.Arguments().at('a').getType());
    STRCMP_EQUAL("arg", command.Arguments().at('a').asString().data());
}

TEST(CommandTest, TwoArguments)
{
    const char text[] = "hello -aarg -u5F";
    const char expectedName[] = "hello";
    unsigned long hex;

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK_EQUAL(2, command.Arguments().size());

    CHECK(command.Arguments().contains('a'));
    CHECK(Argument::Type::STRING == command.Arguments().at('a').getType());
    STRCMP_EQUAL("arg", command.Arguments().at('a').asString().data());

    CHECK(command.Arguments().contains('u'));
    CHECK(Argument::Type::HEX == command.Arguments().at('u').getType());
    CHECK(command.Arguments().at('u').asHex(hex));
    CHECK_EQUAL(0x5F, hex);
}

TEST(CommandTest, TwoArguments_OneEmpty)
{
    const char text[] = "hello -aarg -u";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK_EQUAL(2, command.Arguments().size());

    CHECK(command.Arguments().contains('a'));
    CHECK(Argument::Type::STRING == command.Arguments().at('a').getType());
    STRCMP_EQUAL("arg", command.Arguments().at('a').asString().data());

    CHECK_EQUAL('u', command.Arguments().at('u').getName());
    CHECK(Argument::Type::EMPTY == command.Arguments().at('u').getType());
}

TEST(CommandTest, TwoArguments_OneIvalid)
{
    const char text[] = "hello -aarg -";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK(command.Arguments().empty());
}

TEST(CommandTest, TwoArguments_TwoEmpty)
{
    const char text[] = "hello -a -b";

    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK_EQUAL(2, command.Arguments().size());

    CHECK(command.Arguments().contains('a'));
    CHECK(Argument::Type::EMPTY == command.Arguments().at('a').getType());

    CHECK_EQUAL('b', command.Arguments().at('b').getName());
    CHECK(Argument::Type::EMPTY == command.Arguments().at('b').getType());
}

TEST(CommandTest, TooMuchArguments)
{
    const char text[] = "hello -a -b -c -d -e -f -g -h -i -j -k -l m -n -o -p";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK(command.Arguments().empty());
}

TEST(CommandTest, TwoArguments_NoSpace)
{
    const char text[] = "hello -aarg-u5F";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK(command.Arguments().empty());
}

TEST(CommandTest, TwoHyphens)
{
    const char text[] = "hello --a";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK(command.Arguments().empty());
}