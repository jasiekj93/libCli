#pragma once

/**
 * @file Terminal.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

#include <libcli/ITerminal.hpp>
#include <libcli/IOutput.hpp>
#include <libcli/ICommandObserver.hpp>
#include <libcli/internal/io/InputController.hpp>
#include <libcli/internal/io/OutputController.hpp>
#include <libcli/internal/CommandVerifier.hpp>
#include <libcli/internal/Presenter.hpp>

namespace cli::internal
{
    class Terminal 
        : public ITerminal
        , public io::IInputLineObserver
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

        inline templatessBuffer & templatess() override { return _verifier.templatess(); }

        void PutString(const char *) override;
        size_t Printf(const char *, ...) override;
        virtual void DisableInput() override;
        virtual void EnableInput() override;
        inline bool IsInputEnabled() override { return _isInputEnabled; }

    protected:
        void ReceivedInputLineCallback(const char *) override;

    private:
        ICommandObserver &_observer;
        IOutput &_output;

        io::container::LineBufferWithMemory _inputBuffer;
        io::OutputController _outputController;
        io::InputController _inputController;
        
        Presenter _presenter;
        CommandVerifier _verifier;
        bool _isInputEnabled;
        char *_printfBuffer;
        const size_t _printfBufferSize;
    };
}