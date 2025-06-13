#pragma once

/**
 * @file InputController.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

#include <etl/string.h> 

#include <libcli/internal/io/InputLineObserver.hpp>
#include <libcli/internal/io/ControlSequence.hpp>
#include <libcli/internal/io/ControlChar.hpp>
#include <libcli/internal/io/OutputStreamExtended.hpp>
#include <libcli/internal/io/container/LineBufferWithMemory.hpp>

namespace cli::internal::io
{
    class InputController
    {
    public:
        InputController(OutputStreamExtended&,
            InputLineObserver&,
            container::LineBufferWithMemory&);

        void receivedCharCallback(char);
        void receivedStringCallback(etl::string_view);

        void restoreLine();
        void clearLine(unsigned int extraChars = 0);

    protected:
        bool processControlChar(char c);
        bool processEscapeChar();
        bool processNewLine();
        bool processBackspace();
        bool processTab();
        bool processConrolSequence(char c);
        bool processControlSequenceByType();

        void moveHome();
        void moveEnd();

    private:
        OutputStreamExtended& output;
        InputLineObserver& observer;
        container::LineBufferWithMemory& buffer;

        ControlSequence controlSequence;
    };
}