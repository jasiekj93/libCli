#pragma once

/**
 * @file Presenter.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

#include <libcli/internal/IPresenter.hpp>
#include <libcli/internal/CommandHelper.hpp>
#include <libcli/Configuration.hpp>
#include <cstring>

namespace cli::internal
{
    class Presenter : public IPresenter
    {
    public:
        static constexpr char PROMPT_CHAR = '$';

        Presenter(IOutput &, const char *userName = nullptr);

        void UnknownCommand(const char *) override;
        void NoMandatoryArguments(char argument, const templates::Command &) override;
        void InvalidArgument(char argument, const templates::Command &) override;
        void InvalidArgumentType(char argument, const templates::Command &) override;
        void Help(const templates::Command &) override;
        void Prompt(bool addNewLine = true) override;
        
        inline size_t PromptLength() override { return (std::strlen(_userName) + 2); }
        
        void NewLine();

    protected:

    private:
        IOutput &_output;
        CommandHelper _helper;
        char _userName[Configuration::MAX_USER_NAME + 1];
    };
}