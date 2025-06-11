#include "Factory.hpp"
#include <libcli/internal/TerminalImpl.hpp>

using namespace cli;

std::shared_ptr<Terminal> Factory::createNewTerminal(Output& output, 
    CommandObserver& observer, 
    etl::string_view userName,
    language::Dictionary dictionary)
{
    return std::make_shared<internal::TerminalImpl>(output, 
        observer, 
        userName,
        dictionary);
}
