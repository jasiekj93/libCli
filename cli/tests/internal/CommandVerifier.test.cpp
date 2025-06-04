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
            { 'a', { Argument::Type::DECIMAL, true } },
            { 'b', { Argument::Type::STRING, true } },
            { 'c', { Argument::Type::DOUBLE, true } },
            { 'd', { Argument::Type::HEX, true } },
            { 'e', { Argument::Type::EMPTY, true } },
        });

    verifier.templates()[name] = (commandTemp);
    CHECK(verifier.verify(command));
}

TEST(CommandVerifierTest, MissingMandatoryArgument)
{
    Command command(text);
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);
    templates::Command commandTemp(name,
        {
            { 'a', { Argument::Type::DECIMAL, true } },
            { 'b', { Argument::Type::STRING, true } },
            { 'c', { Argument::Type::DOUBLE, true } },
            { 'd', { Argument::Type::HEX, true } },
            { 'e', { Argument::Type::EMPTY, true } },
            { 'f', { Argument::Type::EMPTY, true } },
        });

    verifier.templates()[name] = (commandTemp);
    CHECK_FALSE(verifier.verify(command));
    CHECK(mock::Presenter::Operation::NoMandatoryArguments == presenter.operation);
}

TEST(CommandVerifierTest, OptionalArgument)
{
    Command command(text);
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);
    templates::Command commandTemp(name,
        {
            { 'a', { Argument::Type::DECIMAL, true } },
            { 'b', { Argument::Type::STRING, true } },
            { 'c', { Argument::Type::DOUBLE, true } },
            { 'd', { Argument::Type::HEX, true } },
            { 'e', { Argument::Type::EMPTY, false } },
        });

    verifier.templates()[name] = (commandTemp);
    CHECK(verifier.verify(command));
}

TEST(CommandVerifierTest, OptionalArgument_IsMissing)
{
    Command command(text);
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);
    templates::Command commandTemp(name,
        {
            { 'a', { Argument::Type::DECIMAL, true } },
            { 'b', { Argument::Type::STRING, true } },
            { 'c', { Argument::Type::DOUBLE, true } },
            { 'd', { Argument::Type::HEX, true } },
            { 'e', { Argument::Type::EMPTY, false } },
            { 'f', { Argument::Type::EMPTY, false } },
        });

    verifier.templates()[name] = (commandTemp);
    CHECK(verifier.verify(command));
}

TEST(CommandVerifierTest, NotDefinedArgument)
{
    Command command(text);
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);
    templates::Command commandTemp(name,
        {
            { 'a', { Argument::Type::DECIMAL, true } },
            { 'b', { Argument::Type::STRING, true } },
            { 'c', { Argument::Type::DOUBLE, true } },
            { 'd', { Argument::Type::HEX, false } },
        });

    verifier.templates()[name] = (commandTemp);
    CHECK_FALSE(verifier.verify(command));
    CHECK(mock::Presenter::Operation::InvalidArgument == presenter.operation);
}

TEST(CommandVerifierTest, DifferentType)
{
    Command command(text);
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);
    templates::Command commandTemp(name,
        {
            { 'a', { Argument::Type::STRING, true } },
            { 'b', { Argument::Type::STRING, true } },
            { 'c', { Argument::Type::DOUBLE, true } },
            { 'd', { Argument::Type::HEX, true } },
            { 'e', { Argument::Type::EMPTY, false } },
        });

    verifier.templates()[name] = (commandTemp);
    CHECK_FALSE(verifier.verify(command));
    CHECK(mock::Presenter::Operation::InvalidArgumentType == presenter.operation);
}

TEST(CommandVerifierTest, DifferentType_Optional)
{
    Command command(text);
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);
    templates::Command commandTemp(name,
        {
            { 'a', { Argument::Type::STRING, false } },
            { 'b', { Argument::Type::STRING, true } },
            { 'c', { Argument::Type::DOUBLE, true } },
            { 'd', { Argument::Type::HEX, true } },
            { 'e', { Argument::Type::EMPTY, false } },
        });

    verifier.templates()[name] = (commandTemp);
    CHECK_FALSE(verifier.verify(command));
    CHECK(mock::Presenter::Operation::InvalidArgumentType == presenter.operation);

}

TEST(CommandVerifierTest, WithHelp)
{
    Command command(textWihHelp);
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);
    templates::Command commandTemp(name,
        {
            { 'a', { Argument::Type::DECIMAL, true } },
            { 'b', { Argument::Type::STRING, true } },
            { 'c', { Argument::Type::DOUBLE, true } },
            { 'd', { Argument::Type::HEX, true } },
            { 'e', { Argument::Type::EMPTY, false } },
        });

    verifier.templates()[name] = (commandTemp);
    CHECK_FALSE(verifier.verify(command));
    CHECK(mock::Presenter::Operation::Help == presenter.operation);
}

TEST(CommandVerifierTest, CustomHelp)
{
    Command command(textWihHelp);
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);
    templates::Command commandTemp(name,
        {
            { 'a', { Argument::Type::DECIMAL, true } },
            { 'b', { Argument::Type::STRING, true } },
            { 'c', { Argument::Type::DOUBLE, true } },
            { 'd', { Argument::Type::HEX, true } },
            { 'e', { Argument::Type::EMPTY, false } },
            { 'h', { Argument::Type::EMPTY, false } },
        });

    verifier.templates()[name] = (commandTemp);
    CHECK(verifier.verify(command));
}

TEST(CommandVerifierTest, Find)
{
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);

    verifier.templates()["foo"] = templates::Command("foo");
    verifier.templates()["bar"] = templates::Command("bar");
    verifier.templates()["baz"] = templates::Command("baz");

    auto found = verifier.find("f");

    CHECK(found != nullptr);
    STRCMP_EQUAL("foo", found.data());
}

TEST(CommandVerifierTest, Find_TwoAreMatch)
{
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);

    verifier.templates()["foo"] = templates::Command("foo");
    verifier.templates()["bar"] = templates::Command("bar");
    verifier.templates()["baz"] = templates::Command("baz");

    auto found = verifier.find("b");

    CHECK(found != nullptr);
    STRCMP_EQUAL("bar", found.data());
}

TEST(CommandVerifierTest, Find_SubstringMatchComaand)
{
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);

    verifier.templates()["foo"] = templates::Command("foo");
    verifier.templates()["bar"] = templates::Command("bar");
    verifier.templates()["baz"] = templates::Command("baz");

    auto found = verifier.find("baz");

    CHECK(found == nullptr);
}

TEST(CommandVerifierTest, Find_SubstringAreLongerThanCommand)
{
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);

    verifier.templates()["foo"] = templates::Command("foo");
    verifier.templates()["bar"] = templates::Command("bar");
    verifier.templates()["baz"] = templates::Command("baz");

    auto found = verifier.find("baz -t");

    CHECK(found == nullptr);
}

TEST(CommandVerifierTest, SpacesOnTheBeggining)
{
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);

    verifier.templates()["foo"] = templates::Command("foo");
    verifier.templates()["bar"] = templates::Command("bar");
    verifier.templates()["baz"] = templates::Command("baz");

    auto found = verifier.find(" baz");

    CHECK(found == nullptr);
}

TEST(CommandVerifierTest, EmptyString)
{
    mock::Presenter presenter;
    CommandVerifier verifier(presenter);

    verifier.templates()["foo"] = templates::Command("foo");
    verifier.templates()["bar"] = templates::Command("bar");
    verifier.templates()["baz"] = templates::Command("baz");

    auto found = verifier.find("");

    CHECK(found == nullptr);
}