#include "Presenter.hpp"

using namespace mock;

void Presenter::UnknownCommand(const char *)
{
    operation = Operation::UnknownCommand;
}

void Presenter::NoMandatoryArguments(char argument, const cli::templates::Command &)
{
    operation = Operation::NoMandatoryArguments;
}

void Presenter::InvalidArgument(char argument, const cli::templates::Command &)
{
    operation = Operation::InvalidArgument;
}

void Presenter::InvalidArgumentType(char argument, const cli::templates::Command &)
{
    operation = Operation::InvalidArgumentType;
}

void Presenter::Help(const cli::templates::Command &)
{
    operation = Operation::Help;
}

void Presenter::Prompt(bool)
{
    operation = Operation::Prompt;
}
