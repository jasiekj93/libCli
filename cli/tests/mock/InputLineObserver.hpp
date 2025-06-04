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
        InputLineObserver(size_t);
        ~InputLineObserver();

        void receivedInputLineCallback(etl::string_view) override;
        etl::string_view receivedAutoCompleteCallback(etl::string_view) override { return ""; }

        char* line;

    private:
        InputLineObserver(const InputLineObserver&) = delete;
        auto operator=(const InputLineObserver&) = delete;
    };
}