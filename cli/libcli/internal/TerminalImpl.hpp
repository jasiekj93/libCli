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
        TerminalImpl(Output&,
            CommandObserver&,
            etl::string_view userName,
            size_t printBufferSize);

        ~TerminalImpl();

        void receivedCharCallback(char) override;
        void receivedStringCallback(const char *) override;
        etl::string_view receivedAutoCompleteCallback(etl::string_view) override;

        inline TemplatesBuffer& templates() override { return verifier.templates(); }

        void putString(const char *) override;
        size_t printf(const char *, ...) override;
        virtual void disableInput() override;
        virtual void enableInput() override;
        inline bool isInputEnabled() override { return inputEnabledFlag; }

    protected:
        void receivedInputLineCallback(etl::string_view) override;

    private:
        CommandObserver& observer;
        Output& output;

        io::container::LineBufferWithMemory inputBuffer;
        io::OutputControllerImpl outputController;
        io::InputController inputController;
        
        PresenterImpl presenter;
        CommandVerifier verifier;
        bool inputEnabledFlag;
        char* printfBuffer;
        const size_t printfBufferSize;
    };
}