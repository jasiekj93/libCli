#include "InputController.hpp"
#include <cctype>
#include <cstring>

using namespace cli::internal::io;

InputController::InputController(IOutputController &output, 
    IInputLineObserver &observer,
    container::LineBufferWithMemory &buffer)
    : _output(output)
    , _observer(observer)
    , _buffer(buffer)
{
}

void InputController::ReceivedCharCallback(char c)
{
    if(_ProcessControlChar(c) == true)
        return;
    
    if(std::isprint(c))
    {
        if(_buffer.Put(c) == true)
            _output.PutChar(c);
    }
}

void InputController::ReceivedStringCallback(const char *string)
{
    auto length = std::strlen(string);

    for(size_t i = 0; i < length; i++)
        ReceivedCharCallback(string[i]);
}

void InputController::RestoreLine()
{
    _output.PutString(_buffer.Data());
    _buffer.MoveCursorMaxRight();
}

void InputController::ClearLine(unsigned int extraChars)
{
    _MoveEnd();
    _output.Backspace(_buffer.Count());
    _output.Backspace(extraChars);
}

bool InputController::_ProcessControlChar(char c)
{
    if(c == ControlChar::ESCAPE_CHAR)
        return _ProcessEscapeChar();
    else if(c == ControlChar::NEW_LINE)
        return _ProcessNewLine();
    else if(c == ControlChar::BACKSPACE)
        return _ProcessBackspace();
    else if(c == ControlChar::TAB)
        return _ProcessTab();
    else if(_controlSequence.IsNotEmpty())
        return _ProcessConrolSequence(c);
    else
        return false;
}

bool InputController::_ProcessEscapeChar()
{
    _controlSequence.Clear();
    _controlSequence.Put(ControlChar::ESCAPE_CHAR);
    return true;
}

bool InputController::_ProcessNewLine()
{
    _output.NewLine();
    _observer.ReceivedInputLineCallback(_buffer.Data());
    _buffer.ClearAndMemorize();

    return true;
}

bool InputController::_ProcessBackspace()
{
    if(_buffer.Count() == _buffer.Cursor() &&
        (_buffer.MoveCursorLeft() == true))
    {
        _buffer.Delete();
        _output.Backspace();
    }

    return true;
}

bool InputController::_ProcessTab()
{
    auto result = _observer.ReceivedAutoComapleteCallback(_buffer.Data());

    if(result != nullptr)
    {
        ClearLine();
        
        _buffer.Clear();
        _buffer.PutString(result);
        
        _output.PutString(result);
    }

    return true;
}

bool InputController::_ProcessConrolSequence(char c)
{
    _controlSequence.Put(c);

    if(_ProcessControlSequenceByType() == true)
        _controlSequence.Clear();

    if(_controlSequence.IsFull())
        _controlSequence.Clear();
    
    return true;
}

bool InputController::_ProcessControlSequenceByType()
{
    auto type = _controlSequence.GetType();
    
    switch(type)
    {
        case ControlSequence::Type::Delete:
            if(_buffer.Delete() == true)
                _output.Delete();
            break;
        // case ControlSequence::Type::ArrowLeft:
        //     if(_buffer.MoveCursorLeft() == true)
        //         _output.MoveCursorLeft();
        //     break;
        // case ControlSequence::Type::ArrowRight:
        //     if (_buffer.MoveCursorRight() == true)
        //         _output.MoveCursorRight();
        //     break;
        // case ControlSequence::Type::End:
        //     _MoveEnd();
        //     break;
        // case ControlSequence::Type::Home:
        //     _MoveHome();
        //     break;
        case ControlSequence::Type::ArrowUp:
            if(_buffer.HasPrevious() == true)
            {
                ClearLine();
                _buffer.SetPrevious();
                _output.PutString(_buffer.Data());
            }
            break;
        case ControlSequence::Type::ArrowDown:
            if(_buffer.HasNext() == true)
            {
                ClearLine();
                _buffer.SetNext();
                _output.PutString(_buffer.Data());
            }
            break;
        default:
            return false;
    }

    return true;
}

void InputController::_MoveHome()
{
    // while(_buffer.MoveCursorLeft())
    //     _output.MoveCursorLeft();

    auto times = _buffer.MoveCursorMaxLeft();

    while(times != 0)
    {
        _output.MoveCursorLeft(times);
        times = _buffer.MoveCursorMaxLeft();
    }
}

void InputController::_MoveEnd()
{
    // while(_buffer.MoveCursorRight())
    //     _output.MoveCursorRight();

    auto times = _buffer.MoveCursorMaxRight();

    while(times != 0)
    {
        _output.MoveCursorRight(times);
        times = _buffer.MoveCursorMaxRight();
    }
}