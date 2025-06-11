#pragma once

/**
 * @file Command.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

#include <etl/string.h>
#include <etl/map.h>
#include <etl/array.h>

#include <libcli/Configuration.hpp>
#include <libcli/model/Argument.hpp>

namespace cli::model
{
    class Command
    {
    public:
        using Arguments = etl::map<char, Argument, Configuration::MAX_ARGUMENT_COUNT>;

        Command();
        Command(etl::string_view);

        inline auto isNull() const { return name.empty(); }
        inline auto& getName() const { return name; }
        inline const auto& getArguments() const { return arguments; }

    protected:
        bool findName();
        bool findArguments();
        unsigned int hyphenCount(const char*) const;

    private:
        etl::array<char, Configuration::MAX_LINE_LENGTH + 1> buffer;
        etl::string_view name;
        Arguments arguments;
    };
}