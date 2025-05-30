#pragma once

/**
 * @file InputLineObserver.hpp
 * @author Adrian Szczepanski
 * @date 27-07-2021
 * @brief 
 * @details
 */

#include <libcli/Internal/IO/IInputLineObserver.hpp>
#include <cstddef>

namespace Mock
{
    class InputLineObserver : public cli::Internal::IO::IInputLineObserver
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