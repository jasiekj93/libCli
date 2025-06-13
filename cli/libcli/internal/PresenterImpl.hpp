#pragma once

/**
 * @file PresenterImpl.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

#include <etl/string.h>

#include <libcli/Configuration.hpp>
#include <libcli/IOStream.hpp>
#include <libcli/Language.hpp>
#include <libcli/internal/Presenter.hpp>
#include <libcli/internal/CommandHelper.hpp>

namespace cli::internal
{
    class PresenterImpl : public Presenter
    {
    public:
        static constexpr char PROMPT_CHAR = '$';

        PresenterImpl(OutputStream&, etl::string_view userName = "", language::Dictionary = language::english);

        void unknownCommand(etl::string_view) override;
        void noMandatoryArguments(char argument, const templates::Command&) override;
        void invalidArgument(char argument, const templates::Command&) override;
        void invalidArgumentType(char argument, const templates::Command&) override;
        void help(const templates::Command&) override;
        void prompt(bool addNewLine = true) override;
        
        inline size_t promptLength() override { return (userName.size() + 2); }
        
    private:
        OutputStream& output;
        CommandHelper helper;
        etl::string<Configuration::MAX_USER_NAME> userName;
        language::Dictionary dictionary;
    };
}