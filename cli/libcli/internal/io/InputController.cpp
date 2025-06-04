#include "InputController.hpp"
#include <cctype>
#include <cstring>

using namespace cli::internal::io;

InputController::InputController(OutputController& output, 
    InputLineObserver& observer,
    container::LineBufferWithMemory& buffer)
    : output(output)
    , observer(observer)
    , buffer(buffer)
{
}

void InputController::receivedCharCallback(char c)
{
    if(processControlChar(c) == true)
        return;
    
    if(std::isprint(c))
    {
        if(buffer.put(c) == true)
            output.putChar(c);
    }
}

void InputController::receivedStringCallback(etl::string_view string)
{
    for(auto& c : string)
        receivedCharCallback(c);
}

void InputController::restoreLine()
{
    output.putString(buffer.data());
    buffer.moveCursorMaxRight();
}

void InputController::clearLine(unsigned int extraChars)
{
    moveEnd();
    output.backspace(buffer.count());
    output.backspace(extraChars);
}

bool InputController::processControlChar(char c)
{
    if(c == ControlChar::ESCAPE_CHAR)
        return processEscapeChar();
    else if(c == ControlChar::NEW_LINE)
        return processNewLine();
    else if(c == ControlChar::BACKSPACE)
        return processBackspace();
    else if(c == ControlChar::TAB)
        return processTab();
    else if(not controlSequence.isEmpty())
        return processConrolSequence(c);
    else
        return false;
}

bool InputController::processEscapeChar()
{
    controlSequence.clear();
    controlSequence.put(ControlChar::ESCAPE_CHAR);
    return true;
}

bool InputController::processNewLine()
{
    output.newLine();
    observer.receivedInputLineCallback(buffer.data());
    buffer.clearAndMemorize();

    return true;
}

bool InputController::processBackspace()
{
    if(buffer.count() == buffer.cursor() &&
        (buffer.moveCursorLeft() == true))
    {
        buffer.remove();
        output.backspace();
    }

    return true;
}

bool InputController::processTab()
{
    auto result = observer.receivedAutoCompleteCallback(buffer.data());

    if(result != nullptr)
    {
        clearLine();
        
        buffer.clear();
        buffer.putString(result.data());

        output.putString(result.data());
    }

    return true;
}

bool InputController::processConrolSequence(char c)
{
    controlSequence.put(c);

    if(processControlSequenceByType() == true)
        controlSequence.clear();

    if(controlSequence.isFull())
        controlSequence.clear();
    
    return true;
}

bool InputController::processControlSequenceByType()
{
    auto type = controlSequence.getType();
    
    switch(type)
    {
        case ControlSequence::Type::DELETE:
            if(buffer.remove() == true)
                output.putDelete();
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
        case ControlSequence::Type::ARROW_UP:
            if(buffer.hasPrevious() == true)
            {
                clearLine();
                buffer.setPrevious();
                output.putString(buffer.data());
            }
            break;
        case ControlSequence::Type::ARROW_DOWN:
            if(buffer.hasNext() == true)
            {
                clearLine();
                buffer.setNext();
                output.putString(buffer.data());
            }
            break;
        default:
            return false;
    }

    return true;
}

void InputController::moveHome()
{
    // while(_buffer.MoveCursorLeft())
    //     _output.MoveCursorLeft();

    auto times = buffer.moveCursorMaxLeft();

    while(times != 0)
    {
        output.moveCursorLeft(times);
        times = buffer.moveCursorMaxLeft();
    }
}

void InputController::moveEnd()
{
    // while(_buffer.MoveCursorRight())
    //     _output.MoveCursorRight();

    auto times = buffer.moveCursorMaxRight();

    while(times != 0)
    {
        output.moveCursorRight(times);
        times = buffer.moveCursorMaxRight();
    }
}