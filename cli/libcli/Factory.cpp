#include "Factory.hpp"
#include <libcli/internal/TerminalImpl.hpp>

using namespace cli;

Terminal* Factory::createNewTerminal(Output& output, 
    CommandObserver& observer, 
    size_t depth,
    const char* userName,
    size_t printfBufferSize)
{
    return new internal::TerminalImpl(output, 
        observer, 
        depth, 
        userName, 
        printfBufferSize);
}
