#pragma once

#include <libCli/ITerminal.hpp>
#include <libCli/IOutput.hpp>
#include <libCli/ICommandObserver.hpp>
#include <libCli/Internal/IO/InputController.hpp>
#include <libCli/Internal/IO/OutputController.hpp>
#include <libCli/Internal/CommandVerifier.hpp>
#include <libCli/Internal/Presenter.hpp>

namespace Cli::Internal
{
    class Terminal 
        : public ITerminal
        , public IO::IInputLineObserver
    {
    public:
        Terminal(IOutput &,
            ICommandObserver &,
            size_t depth);

        void ReceivedCharCallback(char) override;
        void ReceivedStringCallback(const char *) override;
        inline TemplatesBuffer & Templates() override { return _verifier.Templates(); }

    protected:
        void ReceivedInputLineCallback(const char *) override;

    private:
        ICommandObserver &_observer;

        IO::Container::LineBufferWithMemory _inputBuffer;
        IO::OutputController _outputController;
        IO::InputController _inputController;
        
        Presenter _presenter;
        CommandVerifier _verifier;
    };
}