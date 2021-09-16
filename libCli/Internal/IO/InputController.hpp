#pragma once

/**
 * @file InputController.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

#include <libCli/Internal/IO/IInputLineObserver.hpp>
#include <libCli/Internal/IO/ControlSequence.hpp>
#include <libCli/Internal/IO/ControlChar.hpp>
#include <libCli/Internal/IO/Container/LineBufferWithMemory.hpp>
#include <libCli/Internal/IO/IOutputController.hpp>

namespace Cli::Internal::IO
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
        void _ClearLine();

    private:
        IOutputController &_output;
        IInputLineObserver &_observer;
        Container::LineBufferWithMemory &_buffer;

        ControlSequence _controlSequence;
    };
}