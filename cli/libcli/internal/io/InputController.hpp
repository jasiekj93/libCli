#pragma once

/**
 * @file InputController.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

#include <libcli/internal/io/IInputLineObserver.hpp>
#include <libcli/internal/io/ControlSequence.hpp>
#include <libcli/internal/io/ControlChar.hpp>
#include <libcli/internal/io/container/LineBufferWithMemory.hpp>
#include <libcli/internal/io/IOutputController.hpp>

namespace cli::internal::io
{
    class InputController
    {
    public:
        InputController(IOutputController &, 
        IInputLineObserver &,
        container::LineBufferWithMemory &);

        void ReceivedCharCallback(char);
        void ReceivedStringCallback(const char *);

        void RestoreLine();
        void ClearLine(unsigned int extraChars = 0);

    protected:
        bool _ProcessControlChar(char c);
        bool _ProcessEscapeChar();
        bool _ProcessNewLine();
        bool _ProcessBackspace();
        bool _ProcessTab();
        bool _ProcessConrolSequence(char c);
        bool _ProcessControlSequenceByType();

        void _MoveHome();
        void _MoveEnd();

    private:
        IOutputController &_output;
        IInputLineObserver &_observer;
        container::LineBufferWithMemory &_buffer;

        ControlSequence _controlSequence;
    };
}