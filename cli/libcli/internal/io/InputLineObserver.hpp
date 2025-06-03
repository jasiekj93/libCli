#pragma once

/**
 * @file InputLineObserver.hpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

namespace cli::internal::io
{
    class InputLineObserver
    {
    public:
        virtual ~InputLineObserver() {}

        virtual void ReceivedInputLineCallback(const char*) = 0;
        virtual const char * ReceivedAutoCompleteCallback(const char*) = 0;
    };
}