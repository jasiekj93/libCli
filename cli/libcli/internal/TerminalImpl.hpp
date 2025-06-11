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
#include <libcli/internal/io/OutputControllerExtendedImpl.hpp>
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
            etl::string_view userName);

        void receivedCharCallback(char) override;
        void receivedStringCallback(const char *) override;
        etl::string_view receivedAutoCompleteCallback(etl::string_view) override;

        inline TemplatesBuffer& templates() override { return verifier.templates(); }

        OutputController& operator<<(char) override;
        OutputController& operator<<(etl::string_view) override;
        OutputController& operator<<(const formatspec::Base&) override;

        virtual void disableInput() override;
        virtual void enableInput() override;
        inline bool isInputEnabled() override { return inputEnabledFlag; }

    protected:
        void receivedInputLineCallback(etl::string_view) override;
        OutputController& putString(etl::string_view);

    private:
        CommandObserver& observer;

        io::container::LineBufferWithMemory inputBuffer;
        io::OutputControllerExtendedImpl outputController;
        io::InputController inputController;
        
        PresenterImpl presenter;
        CommandVerifier verifier;
        bool inputEnabledFlag;
    };
}