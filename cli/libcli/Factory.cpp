#include "Factory.hpp"
#include <libcli/internal/Terminal.hpp>

using namespace cli;

ITerminal * Factory::CreateNewTerminal(IOutput &output, 
    ICommandObserver &observer, 
    size_t depth,
    const char *userName,
    size_t printfBufferSize)
{
    return new internal::Terminal(output, 
        observer, 
        depth, 
        userName, 
        printfBufferSize);
}
