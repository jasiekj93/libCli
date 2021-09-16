#pragma once

/**
 * @file Presenter.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

#include <libCli/Internal/IPresenter.hpp>
#include <libCli/Internal/CommandHelper.hpp>
#include <libCli/Configuration.hpp>

namespace Cli::Internal
{
    class Presenter : public IPresenter
    {
    public:
        static constexpr char PROMPT_CHAR = '$';

        Presenter(IOutput &, const char *userName = nullptr);

        void UnknownCommand(const char *) override;
        void NoMandatoryArguments(char argument, const Template::Command &) override;
        void InvalidArgument(char argument, const Template::Command &) override;
        void InvalidArgumentType(char argument, const Template::Command &) override;
        void Help(const Template::Command &) override;
        void Prompt(bool addNewLine = true) override;
        
        void NewLine();

    protected:

    private:
        IOutput &_output;
        CommandHelper _helper;
        char _userName[Configuration::MAX_USER_NAME + 1];
    };
}