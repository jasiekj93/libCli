#pragma once

/**
 * @file ICommandObserver.hpp
 * @author Adrian Szczepanski
 * @date 04-08-2021
 * @brief 
 * @details
 */

#include <libcli/Model/Command.hpp>

namespace cli
{
    class ICommandObserver
    {
    public:
        virtual ~ICommandObserver() {}

        virtual void ReceivedCommandCallback(const Model::Command &) = 0;
    };
}