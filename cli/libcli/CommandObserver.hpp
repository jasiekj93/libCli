#pragma once

/**
 * @file CommandObserver.hpp
 * @author Adrian Szczepanski
 * @date 04-08-2021
 * @brief 
 * @details
 */

#include <libcli/model/Command.hpp>

namespace cli
{
    class CommandObserver
    {
    public:
        virtual ~CommandObserver() {}

        virtual void receivedCommandCallback(const model::Command&) = 0;
    };
}