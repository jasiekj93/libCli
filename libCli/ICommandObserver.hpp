#pragma once

/**
 * @file ICommandObserver.hpp
 * @author Adrian Szczepanski
 * @date 04-08-2021
 * @brief 
 * @details
 */

#include <libCli/Model/Command.hpp>

namespace Cli
{
    class ICommandObserver
    {
    public:
        virtual ~ICommandObserver() {}

        virtual void ReceivedCommandCallback(const Model::Command &) = 0;
    };
}