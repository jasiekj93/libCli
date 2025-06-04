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
    CHECK_EQUAL(0, command.Arguments().Count());
}


TEST(CommandTest, OnlyName)
{   
    const char text[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(text, command.GetName());
    CHECK_EQUAL(0, command.Arguments().Count());
}

TEST(CommandTest, TooLongNameName)
{   
    const char text[] = "helloThisIsVeryLongCommandTooBigToBeHandledByThisLibrary";

    Command command(text);

    CHECK(command.IsNull());
    CHECK(nullptr == command.GetName());
    CHECK_EQUAL(0, command.Arguments().Count());
}

TEST(CommandTest, OnlyName_SpacesAtBeginning)
{   
    const char text[] = "   hello";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK_EQUAL(0, command.Arguments().Count());
}

TEST(CommandTest, TwoWords_NotAnArgument)
{
    const char text[] = "hello world";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK_EQUAL(0, command.Arguments().Count());
}

TEST(CommandTest, OneArgument)
{
    const char text[] = "hello -a arg";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK_EQUAL(1, command.Arguments().Count());

    CHECK_EQUAL('a', command.Arguments()[0].getName());
    CHECK(Argument::Type::STRING == command.Arguments()[0].getType());
    STRCMP_EQUAL("arg", command.Arguments()[0].asString().data());
}

TEST(CommandTest, OneArgument_MoreSpaces)
{
    const char text[] = "    hello     -a     arg    ";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK_EQUAL(1, command.Arguments().Count());

    CHECK_EQUAL('a', command.Arguments()[0].getName());
    CHECK(Argument::Type::STRING == command.Arguments()[0].getType());
    STRCMP_EQUAL("arg", command.Arguments()[0].asString().data());
}

TEST(CommandTest, OneArgument_NoSpace)
{
    const char text[] = "hello -aarg";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK_EQUAL(1, command.Arguments().Count());

    CHECK_EQUAL('a', command.Arguments()[0].getName());
    CHECK(Argument::Type::STRING == command.Arguments()[0].getType());
    STRCMP_EQUAL("arg", command.Arguments()[0].asString().data());
}

TEST(CommandTest, TwoArguments)
{
    const char text[] = "hello -aarg -u5F";
    const char expectedName[] = "hello";
    unsigned long hex;

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK_EQUAL(2, command.Arguments().Count());

    CHECK_EQUAL('a', command.Arguments()[0].getName());
    CHECK(Argument::Type::STRING == command.Arguments()[0].getType());
    STRCMP_EQUAL("arg", command.Arguments()[0].asString().data());

    CHECK_EQUAL('u', command.Arguments()[1].getName());
    CHECK(Argument::Type::HEX == command.Arguments()[1].getType());
    CHECK(command.Arguments()[1].asHex(hex));
    CHECK_EQUAL(0x5F, hex);
}

TEST(CommandTest, TwoArguments_OneEmpty)
{
    const char text[] = "hello -aarg -u";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK_EQUAL(2, command.Arguments().Count());

    CHECK_EQUAL('a', command.Arguments()[0].getName());
    CHECK(Argument::Type::STRING == command.Arguments()[0].getType());
    STRCMP_EQUAL("arg", command.Arguments()[0].asString().data());

    CHECK_EQUAL('u', command.Arguments()[1].getName());
    CHECK(Argument::Type::EMPTY == command.Arguments()[1].getType());
}

TEST(CommandTest, TwoArguments_OneIvalid)
{
    const char text[] = "hello -aarg -";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK_EQUAL(0, command.Arguments().Count());
}

TEST(CommandTest, TwoArguments_TwoEmpty)
{
    const char text[] = "hello -a -b";

    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK_EQUAL(2, command.Arguments().Count());

    CHECK_EQUAL('a', command.Arguments()[0].getName());
    CHECK(Argument::Type::EMPTY == command.Arguments()[0].getType());

    CHECK_EQUAL('b', command.Arguments()[1].getName());
    CHECK(Argument::Type::EMPTY == command.Arguments()[1].getType());
}

TEST(CommandTest, TooMuchArguments)
{
    const char text[] = "hello -a -b -c -d -e -f -g -h -i -j -k -l m -n -o -p";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK_EQUAL(0, command.Arguments().Count());
}

TEST(CommandTest, TwoArguments_NoSpace)
{
    const char text[] = "hello -aarg-u5F";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK_EQUAL(0, command.Arguments().Count());
}

TEST(CommandTest, TwoHyphens)
{
    const char text[] = "hello --a";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.IsNull());
    STRCMP_EQUAL(expectedName, command.GetName());
    CHECK_EQUAL(0, command.Arguments().Count());
}