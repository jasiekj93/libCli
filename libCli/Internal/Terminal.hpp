#pragma once

/**
 * @file Terminal.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

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
            size_t depth,
            const char *userName,
            size_t );

        ~Terminal();

        void ReceivedCharCallback(char) override;
        void ReceivedStringCallback(const char *) override;
        const char * ReceivedAutoComapleteCallback(const char *) override;

        inline TemplatesBuffer & Templates() override { return _verifier.Templates(); }

        void PutString(const char *) override;
        size_t Printf(const char *, ...) override;
        virtual void DisableInput() override;
        virtual void EnableInput() override;

    protected:
        void ReceivedInputLineCallback(const char *) override;

    private:
        ICommandObserver &_observer;
        IOutput &_output;

        IO::Container::LineBufferWithMemory _inputBuffer;
        IO::OutputController _outputController;
        IO::InputController _inputController;
        
        Presenter _presenter;
        CommandVerifier _verifier;
        bool _isInputEnabled;
        char *_printfBuffer;
        const size_t _printfBufferSize;
    };
}