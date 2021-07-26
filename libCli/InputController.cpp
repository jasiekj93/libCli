#include "InputController.hpp"

using namespace Cli;

InputController::InputController(IOutput &output, IInputLineObserver &observer)
    : _output(output)
    , _observer(observer)
{
}

void InputController::ReceivedCharCallback(char c)
{
    if(_ProcessChar(c) == true)
        _output.PutChar(c);
}


bool InputController::_ProcessChar(char c)
{
    if(c == '\n')
        return _ProcessNewLine();
    else if(_controlChar.Count() > 0 || c == ControlCharacter::ESCAPE_CHAR)
        return _ProcessControlChar(c);
    else
        return _ProcessPrintableChar(c);
}

bool InputController::_ProcessControlChar(char c)
{
    auto type = _PutControlChar(c);

    switch (type)
    {
    case /* constant-expression */:
        /* code */
        break;
    
    default:
        break;
    }
}

ControlCharacter::Type InputController::_PutControlChar(char c)
{
    auto type = ControlCharacter::Type::Unknown;

    if(c == ControlCharacter::ESCAPE_CHAR)
    {
        _controlChar.Clear();
        _controlChar.Put(c);
    }
    else if(_controlChar.Count() > 0)
    {
        if(_controlChar.Put(c) == false)
            _controlChar.Clear();
        else
            type = _controlChar.GetType();
    }

    return type;
}

bool InputController::_ProcessNewLine()
{

}

