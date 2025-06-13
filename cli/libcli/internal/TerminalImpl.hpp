#pragma once

/**
 * @file TerminalImpl.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

#include <libcli/Terminal.hpp>
#include <libcli/CommandObserver.hpp>
#include <libcli/StringStream.hpp>
#include <libcli/internal/io/InputController.hpp>
#include <libcli/internal/io/OutputStreamExtended.hpp>
#include <libcli/internal/CommandVerifier.hpp>
#include <libcli/internal/PresenterImpl.hpp>

namespace cli::internal
{
    class TerminalImpl 
        : public Terminal
        , public io::InputLineObserver
    {
    public:
        TerminalImpl(OutputStream&,
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
        void write(char c) override;
        void write(etl::string_view) override;
        void flush() override;
        bool executeCommand(const model::Command&, InputStream&, OutputStream&);
        void cleanAfterExecutions();

    private:
        CommandObserver& observer;

        io::container::LineBufferWithMemory inputBuffer;
        io::OutputStreamExtended output;
        io::InputController inputController;
        
        PresenterImpl presenter;
        CommandVerifier verifier;
        StringStream streams[2];
        bool inputEnabledFlag;
    };
}