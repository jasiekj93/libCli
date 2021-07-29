#pragma once

#include <libCli/IInputLineObserver.hpp>
#include <libCli/ICommandObserver.hpp>

namespace Cli
{
    class CommandController : public IInputLineObserver
    {
    public:
        CommandController(ICommandObserver &);

        void ReceivedInputLineCallback(const char *) override;

    };
}