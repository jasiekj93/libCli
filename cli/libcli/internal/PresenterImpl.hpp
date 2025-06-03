#pragma once

/**
 * @file PresenterImpl.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

#include <cstring>

#include <libcli/Configuration.hpp>
#include <libcli/Output.hpp>
#include <libcli/internal/Presenter.hpp>
#include <libcli/internal/CommandHelper.hpp>

namespace cli::internal
{
    class PresenterImpl : public Presenter
    {
    public:
        static constexpr char PROMPT_CHAR = '$';

        PresenterImpl(Output&, const char *userName = nullptr);

        void UnknownCommand(const char *) override;
        void NoMandatoryArguments(char argument, const templates::Command&) override;
        void InvalidArgument(char argument, const templates::Command&) override;
        void InvalidArgumentType(char argument, const templates::Command&) override;
        void Help(const templates::Command&) override;
        void Prompt(bool addNewLine = true) override;
        
        inline size_t PromptLength() override { return (std::strlen(_userName) + 2); }
        
        void NewLine();

    private:
        Output &_output;
        CommandHelper _helper;
        char _userName[Configuration::MAX_USER_NAME + 1];
    };
}