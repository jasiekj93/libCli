#pragma once

#include <libCli/Internal/IPresenter.hpp>
#include <libCli/Internal/CommandHelper.hpp>

namespace Cli::Internal
{
    class Presenter : public IPresenter
    {
    public:
        static constexpr char PROMPT_CHAR = '$';

        Presenter(IOutput &);

        void InvalidCommandFormat() override;
        void UnknownCommand(const char *) override;
        void NoMandatoryArguments(char argument, const Template::Command &) override;
        void InvalidArgument(char argument, const Template::Command &) override;
        void InvalidArgumentType(char argument, const Template::Command &) override;
        void Help(const Template::Command &) override;
        void Prompt() override;

    protected:
        void _NewLine();

    private:
        IOutput &_output;
        CommandHelper _helper;
    };
}