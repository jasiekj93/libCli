#pragma once

/**
 * @file InputLineObserver.hpp
 * @author Adrian Szczepanski
 * @date 27-07-2021
 * @brief 
 * @details
 */

#include <libcli/internal/io/InputLineObserver.hpp>
#include <cstddef>

namespace mock
{
    class InputLineObserver : public cli::internal::io::InputLineObserver
    {
    public:
        InputLineObserver() = default;

        void receivedInputLineCallback(etl::string_view) override;
        etl::string_view receivedAutoCompleteCallback(etl::string_view) override { return ""; }

        etl::string<1024> line;

    private:
        InputLineObserver(const InputLineObserver&) = delete;
        auto operator=(const InputLineObserver&) = delete;
    };
}