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
#include <libcli/StringStream.hpp>
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
            etl::string_view userName,
            language::Dictionary);

        void receivedCharCallback(char) override;
        void receivedStringCallback(const char *) override;
        etl::string_view receivedAutoCompleteCallback(etl::string_view) override;

        inline TemplatesBuffer& templates() override { return verifier.templates(); }

        virtual void disableInput() override;
        virtual void enableInput() override;
        inline bool isInputEnabled() override { return inputEnabledFlag; }

    protected:
        void receivedInputLineCallback(etl::string_view) override;
        void putString(etl::string_view);
        void write(char c) override;
        void write(etl::string_view) override;
        void flush() override;

    private:
        CommandObserver& observer;

        io::container::LineBufferWithMemory inputBuffer;
        io::OutputControllerExtendedImpl outputController;
        io::InputController inputController;
        
        PresenterImpl presenter;
        CommandVerifier verifier;
        StringStream stream1, stream2;
        bool inputEnabledFlag;
    };
}