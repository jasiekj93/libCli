#include "Presenter.hpp"

using namespace mock;

void Presenter::unknownCommand(etl::string_view)
{
    operation = Operation::UnknownCommand;
}

void Presenter::noMandatoryArguments(char argument, const cli::templates::Command &)
{
    operation = Operation::NoMandatoryArguments;
}

void Presenter::invalidArgument(char argument, const cli::templates::Command &)
{
    operation = Operation::InvalidArgument;
}

void Presenter::invalidArgumentType(char argument, const cli::templates::Command &)
{
    operation = Operation::InvalidArgumentType;
}

void Presenter::help(const cli::templates::Command &)
{
    operation = Operation::Help;
}

void Presenter::prompt(bool)
{
    operation = Operation::Prompt;
}
