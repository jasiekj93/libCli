#pragma once

/**
 * @file OutputController.hpp
 * @author Adrian Szczepanski
 * @date 27-07-2021
 * @brief 
 * @details
 */

#include <etl/string.h>

#include <libcli/internal/io/FormatSpecification.hpp>

namespace cli::internal::io
{
    class OutputController
    {
    public:
        virtual ~OutputController() {}

        virtual OutputController& operator<<(char) = 0;
        virtual OutputController& operator<<(etl::string_view) = 0;
        virtual OutputController& operator<<(const formatspec::Base&) = 0;
        virtual OutputController& operator<<(const formatspec::Repeated&) = 0;
    };
}