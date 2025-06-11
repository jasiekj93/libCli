#pragma once

/**
 * @file OutputControllerExtended.hpp
 * @author Adrian Szczepanski
 * @date 27-07-2021
 * @brief 
 * @details
 */

#include <etl/string.h>

#include <libcli/OutputController.hpp>
#include <libcli/internal/io/FormatSpecificationExtended.hpp>

namespace cli::internal::io
{
    class OutputControllerExtended : public OutputController
    {
    public:
        virtual ~OutputControllerExtended() {}

        virtual OutputController& operator<<(char) override  = 0;
        virtual OutputController& operator<<(etl::string_view) override = 0;
        virtual OutputController& operator<<(const cli::formatspec::Base&) override = 0;

        virtual OutputController& operator<<(const formatspec::Repeated&) = 0;
    };
}