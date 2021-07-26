#pragma once

/**
 * @file IInputLineObserver.hpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

namespace Cli
{
    class IInputLineObserver
    {
    public:
        virtual ~IInputLineObserver() {}

        virtual void ReceivedInputLineCallback(const char *) = 0;
    }
}