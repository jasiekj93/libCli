#pragma once

#include <libCli/IInputLineObserver.hpp>
#include <libCli/ControlChar.hpp>
#include <libCli/Utils/LineBufferWithMemory.hpp>
#include <libCli/IOutputController.hpp>

namespace Cli
{
    class InputController
    {
    public:
        InputController(IOutputController &, 
        IInputLineObserver &,
        Utils::LineBufferWithMemory &);

        void ReceivedCharCallback(char);
        void ReceivedStringCallback(const char *);

    protected:
        bool _ProcessControlChar(char c);
        bool _ProcessEscapeChar();
        bool _ProcessNewLine();
        bool _ProcessBackspace();
        bool _ProcessConrolSequence(char c);
        bool _ProcessControlSequenceByType();

        void _MoveHome();
        void _MoveEnd();
        void _ClearLine();

    private:
        IOutputController &_output;
        IInputLineObserver &_observer;
        Utils::LineBufferWithMemory &_buffer;

        ControlChar _controlChar;
    };
}