#pragma once

/**
 * @file OutputControllerImpl.hpp
 * @author Adrian Szczepanski
 * @date 27-07-2021
 * @brief 
 * @details
 */

#include <libcli/Output.hpp>
#include <libcli/OutputController.hpp>

namespace cli::internal
{
    class OutputControllerImpl : public OutputController
    {
    public:
        OutputControllerImpl(Output&);

        OutputController& operator<<(char) override;
        OutputController& operator<<(etl::string_view) override;
        OutputController& operator<<(const formatspec::Base&) override;

    protected:
        Output& output;
    };
}