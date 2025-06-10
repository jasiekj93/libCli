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

    CHECK(command.isNull());
    CHECK(command.getName().empty());
    CHECK(command.getArguments().empty());
}


TEST(CommandTest, OnlyName)
{   
    const char text[] = "hello";

    Command command(text);

    CHECK_FALSE(command.isNull());
    STRCMP_EQUAL(text, command.getName().data());
    CHECK(command.getArguments().empty());
}

// TEST(CommandTest, TooLongNameName)
// {   
//     const char text[] = "helloThisIsVeryLongCommandTooBigToBeHandledByThisLibrary";

//     Command command(text);

//     CHECK(command.isNull());
//     CHECK(command.getName().empty());
//     CHECK(command.getArguments().empty());
// }

TEST(CommandTest, OnlyName_SpacesAtBeginning)
{   
    const char text[] = "   hello";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.isNull());
    STRCMP_EQUAL(expectedName, command.getName().data());
    CHECK(command.getArguments().empty());
}

TEST(CommandTest, TwoWords_NotAnArgument)
{
    const char text[] = "hello world";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.isNull());
    STRCMP_EQUAL(expectedName, command.getName().data());
    CHECK(command.getArguments().empty());
}

TEST(CommandTest, OneArgument)
{
    const char text[] = "hello -a arg";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.isNull());
    STRCMP_EQUAL(expectedName, command.getName().data());
    CHECK_EQUAL(1, command.getArguments().size());

    CHECK(command.getArguments().contains('a'));
    CHECK(Argument::Type::STRING == command.getArguments().at('a').getType());
    STRCMP_EQUAL("arg", command.getArguments().at('a').asString().data());
}

TEST(CommandTest, OneArgument_MoreSpaces)
{
    const char text[] = "    hello     -a     arg    ";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.isNull());
    STRCMP_EQUAL(expectedName, command.getName().data());
    CHECK_EQUAL(1, command.getArguments().size());

    CHECK(command.getArguments().contains('a'));
    CHECK(Argument::Type::STRING == command.getArguments().at('a').getType());
    STRCMP_EQUAL("arg", command.getArguments().at('a').asString().data());
}

TEST(CommandTest, OneArgument_NoSpace)
{
    const char text[] = "hello -aarg";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.isNull());
    STRCMP_EQUAL(expectedName, command.getName().data());
    CHECK_EQUAL(1, command.getArguments().size());

    CHECK(command.getArguments().contains('a'));
    CHECK(Argument::Type::STRING == command.getArguments().at('a').getType());
    STRCMP_EQUAL("arg", command.getArguments().at('a').asString().data());
}

TEST(CommandTest, TwoArguments)
{
    const char text[] = "hello -aarg -u5F";
    const char expectedName[] = "hello";
    unsigned long hex;

    Command command(text);

    CHECK_FALSE(command.isNull());
    STRCMP_EQUAL(expectedName, command.getName().data());
    CHECK_EQUAL(2, command.getArguments().size());

    CHECK(command.getArguments().contains('a'));
    CHECK(Argument::Type::STRING == command.getArguments().at('a').getType());
    STRCMP_EQUAL("arg", command.getArguments().at('a').asString().data());

    CHECK(command.getArguments().contains('u'));
    CHECK(Argument::Type::HEX == command.getArguments().at('u').getType());
    CHECK(command.getArguments().at('u').asHex(hex));
    CHECK_EQUAL(0x5F, hex);
}

TEST(CommandTest, TwoArguments_OneEmpty)
{
    const char text[] = "hello -aarg -u";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.isNull());
    STRCMP_EQUAL(expectedName, command.getName().data());
    CHECK_EQUAL(2, command.getArguments().size());

    CHECK(command.getArguments().contains('a'));
    CHECK(Argument::Type::STRING == command.getArguments().at('a').getType());
    STRCMP_EQUAL("arg", command.getArguments().at('a').asString().data());

    CHECK_EQUAL('u', command.getArguments().at('u').getName());
    CHECK(Argument::Type::EMPTY == command.getArguments().at('u').getType());
}

TEST(CommandTest, TwoArguments_OneIvalid)
{
    const char text[] = "hello -aarg -";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.isNull());
    STRCMP_EQUAL(expectedName, command.getName().data());
    CHECK(command.getArguments().empty());
}

TEST(CommandTest, TwoArguments_TwoEmpty)
{
    const char text[] = "hello -a -b";

    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.isNull());
    STRCMP_EQUAL(expectedName, command.getName().data());
    CHECK_EQUAL(2, command.getArguments().size());

    CHECK(command.getArguments().contains('a'));
    CHECK(Argument::Type::EMPTY == command.getArguments().at('a').getType());

    CHECK_EQUAL('b', command.getArguments().at('b').getName());
    CHECK(Argument::Type::EMPTY == command.getArguments().at('b').getType());
}

TEST(CommandTest, TooMuchArguments)
{
    const char text[] = "hello -a -b -c -d -e -f -g -h -i -j -k -l m -n -o -p";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.isNull());
    STRCMP_EQUAL(expectedName, command.getName().data());
    CHECK(command.getArguments().empty());
}

TEST(CommandTest, TwoArguments_NoSpace)
{
    const char text[] = "hello -aarg-u5F";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.isNull());
    STRCMP_EQUAL(expectedName, command.getName().data());
    CHECK(command.getArguments().empty());
}

TEST(CommandTest, TwoHyphens)
{
    const char text[] = "hello --a";
    const char expectedName[] = "hello";

    Command command(text);

    CHECK_FALSE(command.isNull());
    STRCMP_EQUAL(expectedName, command.getName().data());
    CHECK(command.getArguments().empty());
}