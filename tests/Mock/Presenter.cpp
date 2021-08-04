#include "Presenter.hpp"

using namespace Mock;

void Presenter::UnknownCommand(const char *)
{
    operation = Operation::UnknownCommand;
}

void Presenter::NoMandatoryArguments(char argument, const Cli::Template::Command &)
{
    operation = Operation::NoMandatoryArguments;
}

void Presenter::InvalidArgument(char argument, const Cli::Template::Command &)
{
    operation = Operation::InvalidArgument;
}

void Presenter::InvalidArgumentType(char argument, const Cli::Template::Command &)
{
    operation = Operation::InvalidArgumentType;
}

void Presenter::Help(const Cli::Template::Command &)
{
    operation = Operation::Help;
}

void Presenter::Prompt(bool)
{
    operation = Operation::Prompt;
}
