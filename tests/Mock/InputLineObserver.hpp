#pragma once

/**
 * @file InputLineObserver.hpp
 * @author Adrian Szczepanski
 * @date 27-07-2021
 * @brief 
 * @details
 */

#include <libCli/IInputLineObserver.hpp>
#include <cstddef>

namespace Mock
{
    class InputLineObserver : public Cli::IInputLineObserver
    {
    public:
        InputLineObserver(size_t);
        ~InputLineObserver();

        void ReceivedInputLineCallback(const char *) override;

        char *line;

    private:
        InputLineObserver(const InputLineObserver &) = delete;
        auto operator=(const InputLineObserver &) = delete;
    };
}