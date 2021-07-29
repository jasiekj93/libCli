#pragma once

/**
 * @file ArgumentBuffer.hpp
 * @author Adrian Szczepanski
 * @date 29-07-2021
 * @brief 
 * @details
 */

#include <libCli/Utils/Buffer.hpp>
#include <libCli/Argument.hpp>
#include <libCli/Configuration.hpp>

namespace Cli::Utils
{
    class ArgumentBuffer 
        : public Buffer<Argument, Configuration::MAX_ARGUMENT_COUNT>
    {
    public:
        bool Put(const Argument &) override;

        bool Contains(char) const;
        int At(char) const;
        const Argument & Get(char);
    
    private:
        static Argument _empty;
    };
}