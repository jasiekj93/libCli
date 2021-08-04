#include "Factory.hpp"
#include <libCli/Internal/Terminal.hpp>

using namespace Cli;

ITerminal * Factory::CreateNewTerminal(IOutput &output, 
    ICommandObserver &observer, 
    size_t depth,
    const char *userName)
{
    return new Internal::Terminal(output, observer, depth, userName);
}
