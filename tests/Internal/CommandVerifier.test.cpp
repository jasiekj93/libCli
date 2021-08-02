/**
 * @file CommandVerifier.test.cpp
 * @author Adrian Szczepanski
 * @date 02-08-2021
 * @brief 
 * @details
 */

#include <libCli/Internal/CommandVerifier.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace Cli;
using namespace Cli::Model;
using namespace Cli::Internal;

static const char *text = "name -a 5 -btext -c 2.0 -d0x2F -e";
static const char *textWihHelp = "name -a 5 -btext -c 2.0 -d0x2F -e -h";
static const char *name = "name";

TEST_GROUP(CommandVerifierTest)
{

};

TEST(CommandVerifierTest, OnlyMandatoryArguments)
{
    Command command(text);
    CommandVerifier verifier;
    Template::Command commandTemp(name,
        {
            { 'a', Argument::Type::Decimal, true },
            { 'b', Argument::Type::String, true },
            { 'c', Argument::Type::Double, true },
            { 'd', Argument::Type::Hex, true },
            { 'e', Argument::Type::Empty, true },
        });

    CHECK(verifier.Templates().Put(commandTemp));
    CHECK(CommandVerifier::Status::Ok == verifier.Verify(command));
}

TEST(CommandVerifierTest, MissingMandatoryArgument)
{
    Command command(text);
    CommandVerifier verifier;
    Template::Command commandTemp(name,
        {
            { 'a', Argument::Type::Decimal, true },
            { 'b', Argument::Type::String, true },
            { 'c', Argument::Type::Double, true },
            { 'd', Argument::Type::Hex, true },
            { 'e', Argument::Type::Empty, true },
            { 'f', Argument::Type::Empty, true },
        });

    CHECK(verifier.Templates().Put(commandTemp));
    CHECK(CommandVerifier::Status::NoMandatoryArguments == verifier.Verify(command));
}

TEST(CommandVerifierTest, OptionalArgument)
{
    Command command(text);
    CommandVerifier verifier;
    Template::Command commandTemp(name,
        {
            { 'a', Argument::Type::Decimal, true },
            { 'b', Argument::Type::String, true },
            { 'c', Argument::Type::Double, true },
            { 'd', Argument::Type::Hex, true },
            { 'e', Argument::Type::Empty, false },
        });

    CHECK(verifier.Templates().Put(commandTemp));
    CHECK(CommandVerifier::Status::Ok == verifier.Verify(command));
}

TEST(CommandVerifierTest, OptionalArgument_IsMissing)
{
    Command command(text);
    CommandVerifier verifier;
    Template::Command commandTemp(name,
        {
            { 'a', Argument::Type::Decimal, true },
            { 'b', Argument::Type::String, true },
            { 'c', Argument::Type::Double, true },
            { 'd', Argument::Type::Hex, true },
            { 'e', Argument::Type::Empty, false },
            { 'f', Argument::Type::Empty, false },
        });

    CHECK(verifier.Templates().Put(commandTemp));
    CHECK(CommandVerifier::Status::Ok == verifier.Verify(command));
}

TEST(CommandVerifierTest, NotDefinedArgument)
{
    Command command(text);
    CommandVerifier verifier;
    Template::Command commandTemp(name,
        {
            { 'a', Argument::Type::Decimal, true },
            { 'b', Argument::Type::String, true },
            { 'c', Argument::Type::Double, true },
            { 'd', Argument::Type::Hex, false },
        });

    CHECK(verifier.Templates().Put(commandTemp));
    CHECK(CommandVerifier::Status::InvalidArgument == verifier.Verify(command));
}

TEST(CommandVerifierTest, DifferentType)
{
    Command command(text);
    CommandVerifier verifier;
    Template::Command commandTemp(name,
        {
            { 'a', Argument::Type::String, true },
            { 'b', Argument::Type::String, true },
            { 'c', Argument::Type::Double, true },
            { 'd', Argument::Type::Hex, true },
            { 'e', Argument::Type::Empty, false },
        });

    CHECK(verifier.Templates().Put(commandTemp));
    CHECK(CommandVerifier::Status::InvalidArgumentType == verifier.Verify(command));
}

TEST(CommandVerifierTest, DifferentType_Optional)
{
    Command command(text);
    CommandVerifier verifier;
    Template::Command commandTemp(name,
        {
            { 'a', Argument::Type::String, false },
            { 'b', Argument::Type::String, true },
            { 'c', Argument::Type::Double, true },
            { 'd', Argument::Type::Hex, true },
            { 'e', Argument::Type::Empty, false },
        });

    CHECK(verifier.Templates().Put(commandTemp));
    CHECK(CommandVerifier::Status::InvalidArgumentType == verifier.Verify(command));
}

TEST(CommandVerifierTest, WithHelp)
{
    Command command(textWihHelp);
    CommandVerifier verifier;
    Template::Command commandTemp(name,
        {
            { 'a', Argument::Type::Decimal, true },
            { 'b', Argument::Type::String, true },
            { 'c', Argument::Type::Double, true },
            { 'd', Argument::Type::Hex, true },
            { 'e', Argument::Type::Empty, false },
        });

    CHECK(verifier.Templates().Put(commandTemp));
    CHECK(CommandVerifier::Status::Help == verifier.Verify(command));
}

TEST(CommandVerifierTest, CustomHelp)
{
    Command command(textWihHelp);
    CommandVerifier verifier;
    Template::Command commandTemp(name,
        {
            { 'a', Argument::Type::Decimal, true },
            { 'b', Argument::Type::String, true },
            { 'c', Argument::Type::Double, true },
            { 'd', Argument::Type::Hex, true },
            { 'e', Argument::Type::Empty, false },
            { 'h', Argument::Type::Empty, false },
        });

    CHECK(verifier.Templates().Put(commandTemp));
    CHECK(CommandVerifier::Status::Ok == verifier.Verify(command));
}