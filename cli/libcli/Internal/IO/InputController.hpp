#pragma once

/**
 * @file InputController.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

#include <libcli/Internal/IO/IInputLineObserver.hpp>
#include <libcli/Internal/IO/ControlSequence.hpp>
#include <libcli/Internal/IO/ControlChar.hpp>
#include <libcli/Internal/IO/Container/LineBufferWithMemory.hpp>
#include <libcli/Internal/IO/IOutputController.hpp>

namespace cli::Internal::IO
{
    class InputController
    {
    public:
        InputController(IOutputController &, 
        IInputLineObserver &,
        Container::LineBufferWithMemory &);

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
        Container::LineBufferWithMemory &_buffer;

        ControlSequence _controlSequence;
    };
}