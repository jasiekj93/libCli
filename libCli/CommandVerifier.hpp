#pragma once

#include <libCli/CommandTemplate.hpp>
#include <libCli/Command.hpp>
#include <libCli/Utils/CommandTemplateBuffer.hpp>

namespace Cli
{
    class CommandVerifier
    {
    public:
        bool Verify(const Command &) const;

        auto & Templates() { return _buffer; }

    private:
        Utils::CommandTemplateBuffer _buffer;
    };
}