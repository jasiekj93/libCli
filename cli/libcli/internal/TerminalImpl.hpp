#pragma once

/**
 * @file TerminalImpl.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

#include <libcli/Terminal.hpp>
#include <libcli/Output.hpp>
#include <libcli/CommandObserver.hpp>
#include <libcli/internal/io/InputController.hpp>
#include <libcli/internal/io/OutputControllerImpl.hpp>
#include <libcli/internal/CommandVerifier.hpp>
#include <libcli/internal/PresenterImpl.hpp>

namespace cli::internal
{
    class TerminalImpl 
        : public Terminal
        , public io::InputLineObserver
    {
    public:
        TerminalImpl(Output &,
            CommandObserver &,
            size_t depth,
            const char *userName,
            size_t );

        ~TerminalImpl();

        void receivedCharCallback(char) override;
        void receivedStringCallback(const char *) override;
        const char * receivedAutoCompleteCallback(const char *) override;

        inline TemplatessBuffer & templates() override { return _verifier.templates(); }

        void putString(const char *) override;
        size_t printf(const char *, ...) override;
        virtual void disableInput() override;
        virtual void enableInput() override;
        inline bool isInputEnabled() override { return _isInputEnabled; }

    protected:
        void receivedInputLineCallback(const char *) override;

    private:
        CommandObserver &_observer;
        Output &_output;

        io::container::LineBufferWithMemory _inputBuffer;
        io::OutputControllerImpl _outputController;
        io::InputController _inputController;
        
        PresenterImpl _presenter;
        CommandVerifier _verifier;
        bool _isInputEnabled;
        char *_printfBuffer;
        const size_t _printfBufferSize;
    };
}