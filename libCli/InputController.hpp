#pragma once

#include <libCli/IOutput.hpp>
#include <libCli/IInputLineObserver.hpp>
#include <libCli/ControlCharacter.hpp>
#include <libCli/Utils/LineBufferWithMemory.hpp>

namespace Cli
{
    class InputController
    {
    public:
        InputController(IOutput &, IInputLineObserver &);

        void ReceivedCharCallback(char);

    protected:
        bool _ProcessChar(char);
        bool _ProcessControlChar(char);
        bool _ProcessNewLine();
        bool _ProcessPrintableChar(char);
        ControlCharacter::Type _PutControlChar(char);

    private:
        IOutput &_output;
        IInputLineObserver &_observer;

        ControlCharacter _controlChar;
        Utils::LineBufferWithMemory<5, 10> _buffer;
    };
}