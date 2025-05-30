/**
 * @file CommandVerifier.test.cpp
 * @author Adrian Szczepanski
 * @date 02-08-2021
 * @brief 
 * @details
 */

#include <libcli/internal/CommandVerifier.hpp>
#include <tests/mock/Presenter.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace cli;
using namespace cli::model;
using namespace cli::internal;

static const char *text = "name -a 5 -btext -c 2.0 -d0x2F -e";
static const char *textWihHelp = "name -a 5 -btext -c 2.0 -d0x2F -e -h";
static const char *name = "name";

TEST_GROUP(CommandVerifierTest)
{

};

TEST(CommandVerifierTest, OnlyMandatoryArguments)
{
    Command command(text);
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);
    templates::Command commandTemp(name,
        {
            { 'a', Argument::Type::Decimal, true },
            { 'b', Argument::Type::String, true },
            { 'c', Argument::Type::Double, true },
            { 'd', Argument::Type::Hex, true },
            { 'e', Argument::Type::Empty, true },
        });

    CHECK(verifier.templatess().Put(commandTemp));
    CHECK(verifier.Verify(command));
}

TEST(CommandVerifierTest, MissingMandatoryArgument)
{
    Command command(text);
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);
    templates::Command commandTemp(name,
        {
            { 'a', Argument::Type::Decimal, true },
            { 'b', Argument::Type::String, true },
            { 'c', Argument::Type::Double, true },
            { 'd', Argument::Type::Hex, true },
            { 'e', Argument::Type::Empty, true },
            { 'f', Argument::Type::Empty, true },
        });

    CHECK(verifier.templatess().Put(commandTemp));
    CHECK_FALSE(verifier.Verify(command));
    CHECK(mock::Presenter::Operation::NoMandatoryArguments == presenter.operation);
}

TEST(CommandVerifierTest, OptionalArgument)
{
    Command command(text);
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);
    templates::Command commandTemp(name,
        {
            { 'a', Argument::Type::Decimal, true },
            { 'b', Argument::Type::String, true },
            { 'c', Argument::Type::Double, true },
            { 'd', Argument::Type::Hex, true },
            { 'e', Argument::Type::Empty, false },
        });

    CHECK(verifier.templatess().Put(commandTemp));
    CHECK(verifier.Verify(command));
}

TEST(CommandVerifierTest, OptionalArgument_IsMissing)
{
    Command command(text);
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);
    templates::Command commandTemp(name,
        {
            { 'a', Argument::Type::Decimal, true },
            { 'b', Argument::Type::String, true },
            { 'c', Argument::Type::Double, true },
            { 'd', Argument::Type::Hex, true },
            { 'e', Argument::Type::Empty, false },
            { 'f', Argument::Type::Empty, false },
        });

    CHECK(verifier.templatess().Put(commandTemp));
    CHECK(verifier.Verify(command));
}

TEST(CommandVerifierTest, NotDefinedArgument)
{
    Command command(text);
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);
    templates::Command commandTemp(name,
        {
            { 'a', Argument::Type::Decimal, true },
            { 'b', Argument::Type::String, true },
            { 'c', Argument::Type::Double, true },
            { 'd', Argument::Type::Hex, false },
        });

    CHECK(verifier.templatess().Put(commandTemp));
    CHECK_FALSE(verifier.Verify(command));
    CHECK(mock::Presenter::Operation::InvalidArgument == presenter.operation);
}

TEST(CommandVerifierTest, DifferentType)
{
    Command command(text);
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);
    templates::Command commandTemp(name,
        {
            { 'a', Argument::Type::String, true },
            { 'b', Argument::Type::String, true },
            { 'c', Argument::Type::Double, true },
            { 'd', Argument::Type::Hex, true },
            { 'e', Argument::Type::Empty, false },
        });

    CHECK(verifier.templatess().Put(commandTemp));
    CHECK_FALSE(verifier.Verify(command));
    CHECK(mock::Presenter::Operation::InvalidArgumentType == presenter.operation);
}

TEST(CommandVerifierTest, DifferentType_Optional)
{
    Command command(text);
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);
    templates::Command commandTemp(name,
        {
            { 'a', Argument::Type::String, false },
            { 'b', Argument::Type::String, true },
            { 'c', Argument::Type::Double, true },
            { 'd', Argument::Type::Hex, true },
            { 'e', Argument::Type::Empty, false },
        });

    CHECK(verifier.templatess().Put(commandTemp));
    CHECK_FALSE(verifier.Verify(command));
    CHECK(mock::Presenter::Operation::InvalidArgumentType == presenter.operation);

}

TEST(CommandVerifierTest, WithHelp)
{
    Command command(textWihHelp);
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);
    templates::Command commandTemp(name,
        {
            { 'a', Argument::Type::Decimal, true },
            { 'b', Argument::Type::String, true },
            { 'c', Argument::Type::Double, true },
            { 'd', Argument::Type::Hex, true },
            { 'e', Argument::Type::Empty, false },
        });

    CHECK(verifier.templatess().Put(commandTemp));
    CHECK_FALSE(verifier.Verify(command));
    CHECK(mock::Presenter::Operation::Help == presenter.operation);
}

TEST(CommandVerifierTest, CustomHelp)
{
    Command command(textWihHelp);
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);
    templates::Command commandTemp(name,
        {
            { 'a', Argument::Type::Decimal, true },
            { 'b', Argument::Type::String, true },
            { 'c', Argument::Type::Double, true },
            { 'd', Argument::Type::Hex, true },
            { 'e', Argument::Type::Empty, false },
            { 'h', Argument::Type::Empty, false },
        });

    CHECK(verifier.templatess().Put(commandTemp));
    CHECK(verifier.Verify(command));
}

TEST(CommandVerifierTest, Find)
{
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);

    verifier.templatess().Put("foo");
    verifier.templatess().Put("bar");
    verifier.templatess().Put("baz");

    auto found = verifier.Find("f");

    CHECK(found != nullptr);
    STRCMP_EQUAL("foo", found);
}

TEST(CommandVerifierTest, Find_TwoAreMatch)
{
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);

    verifier.templatess().Put("foo");
    verifier.templatess().Put("bar");
    verifier.templatess().Put("baz");

    auto found = verifier.Find("b");

    CHECK(found != nullptr);
    STRCMP_EQUAL("bar", found);
}

TEST(CommandVerifierTest, Find_SubstringMatchComaand)
{
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);

    verifier.templatess().Put("foo");
    verifier.templatess().Put("bar");
    verifier.templatess().Put("baz");

    auto found = verifier.Find("baz");

    CHECK(found == nullptr);
}

TEST(CommandVerifierTest, Find_SubstringAreLongerThanCommand)
{
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);

    verifier.templatess().Put("foo");
    verifier.templatess().Put("bar");
    verifier.templatess().Put("baz");

    auto found = verifier.Find("baz -t");

    CHECK(found == nullptr);
}

TEST(CommandVerifierTest, SpacesOnTheBeggining)
{
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);

    verifier.templatess().Put("foo");
    verifier.templatess().Put("bar");
    verifier.templatess().Put("baz");

    auto found = verifier.Find(" baz");

    CHECK(found == nullptr);
}

TEST(CommandVerifierTest, EmptyString)
{
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);

    verifier.templatess().Put("foo");
    verifier.templatess().Put("bar");
    verifier.templatess().Put("baz");

    auto found = verifier.Find("");

    CHECK(found == nullptr);
}