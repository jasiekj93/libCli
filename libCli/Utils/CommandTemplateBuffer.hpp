#pragma once

#include <libCli/Utils/Buffer.hpp>
#include <libCli/Configuration.hpp>
#include <libCli/CommandTemplate.hpp>

namespace Cli::Utils
{
    class CommandTemplateBuffer 
        : public Buffer<CommandTemplate, Configuration::MAX_COMMAND_TEMPLATES_COUNT>
    {
    public:
        bool Put(const CommandTemplate &) override;

        bool Contains(const char *) const;
        int At(const char *) const;
        const CommandTemplate & Get(const char *) const;

    private:
        static CommandTemplate _empty;
    };
}