#pragma once

/**
 * @file ArgumentTemplate.hpp
 * @author Adrian Szczepanski
 * @date 29-07-2021
 * @brief 
 * @details
 */

#include <libCli/Argument.hpp>

namespace Cli
{
    struct ArgumentTemplate
    {
        char name;
        Argument::Type type;
        bool isMandatory;
    };
}