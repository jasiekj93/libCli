#pragma once

/**
 * @file InputLineObserver.hpp
 * @author Adrian Szczepanski
 * @date 27-07-2021
 * @brief 
 * @details
 */

#include <libcli/internal/io/IInputLineObserver.hpp>
#include <cstddef>

namespace mock
{
    class InputLineObserver : public cli::internal::io::IInputLineObserver
    {
    public:
        InputLineObserver(size_t);
        ~InputLineObserver();

        void ReceivedInputLineCallback(const char *) override;
        const char * ReceivedAutoComapleteCallback(const char *) override { return nullptr; }

        char *line;

    private:
        InputLineObserver(const InputLineObserver &) = delete;
        auto operator=(const InputLineObserver &) = delete;
    };
}