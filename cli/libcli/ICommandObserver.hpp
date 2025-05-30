#pragma once

/**
 * @file ICommandObserver.hpp
 * @author Adrian Szczepanski
 * @date 04-08-2021
 * @brief 
 * @details
 */

#include <libcli/model/Command.hpp>

namespace cli
{
    class ICommandObserver
    {
    public:
        virtual ~ICommandObserver() {}

        virtual void ReceivedCommandCallback(const model::Command &) = 0;
    };
}