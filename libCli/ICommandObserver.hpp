#pragma once

/**
 * @file ICommandObserver.hpp
 * @author Adrian Szczepanski
 * @date 29-07-2021
 * @brief 
 * @details
 */

#include <libCli/Command.hpp>

namespace Cli
{
    class ICommandObserver
    {
    public:
        virtual ~ICommandObserver() {}

        virtual bool ReceivedCommandCallback(const Command &) = 0;
    };
}