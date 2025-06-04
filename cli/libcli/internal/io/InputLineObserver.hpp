#pragma once

/**
 * @file InputLineObserver.hpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

#include <etl/string.h>

namespace cli::internal::io
{
    class InputLineObserver
    {
    public:
        virtual ~InputLineObserver() {}

        virtual void receivedInputLineCallback(etl::string_view) = 0;
        virtual etl::string_view receivedAutoCompleteCallback(etl::string_view) = 0;
    };
}