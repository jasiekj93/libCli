#include "InputController.hpp"
#include <cctype>
#include <cstring>

using namespace cli::internal::io;

InputController::InputController(OutputStreamExtended& output, 
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
        if(buffer.push(c) == true)
        {
            output << c;

            if(not buffer.isCursorAtEnd())
            {
                output << buffer.getDataAfterCursor();
                output << cursorLeft(buffer.getCursorCount());
            }
        }
    }
}

void InputController::receivedStringCallback(etl::string_view string)
{
    for(auto& c : string)
        receivedCharCallback(c);
}

void InputController::restoreLine()
{
    output << buffer.getData();
    buffer.moveCursorEnd();
}

void InputController::clearLine(unsigned int extraChars)
{
    moveEnd();
    output << backspace(buffer.getCount());
    output << backspace(extraChars);
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
    output << newLine;
    observer.receivedInputLineCallback(buffer.getData());
    buffer.clearAndMemorize();

    return true;
}

bool InputController::processBackspace()
{
    if(buffer.moveCursorLeft())
    {
        buffer.remove();
        output << backspace();

        if(not buffer.isCursorAtEnd())
        {
            output << buffer.getDataAfterCursor();
            output << ' ';
            output << cursorLeft(buffer.getCursorCount() + 1);
        }
    }

    return true;
}

bool InputController::processDelete()
{
    if(buffer.remove())
    {
        output << deleteChar();

        if(not buffer.isCursorAtEnd())
        {
            output << buffer.getDataAfterCursor();
            output << ' ';
            output << cursorLeft(buffer.getCursorCount() + 1);
        }
    }

    return true;
} 

bool InputController::processTab()
{
    auto result = observer.receivedAutoCompleteCallback(buffer.getData());

    if(result != "")
    {
        clearLine();
        
        buffer.clear();
        buffer.push(result.data());

        output << result;
    }

    return true;
}

bool InputController::processConrolSequence(char c)
{
    if(not controlSequence.put(c))
        return false;

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
            processDelete();
            break;
        case ControlSequence::Type::ARROW_LEFT:
            if(buffer.moveCursorLeft())
                output << cursorLeft();
            break;
        case ControlSequence::Type::ARROW_RIGHT:
            if (buffer.moveCursorRight())
                output << cursorRight();
            break;
        case ControlSequence::Type::END:
            moveEnd();
            break;
        case ControlSequence::Type::HOME:
            moveHome();
            break;
        case ControlSequence::Type::ARROW_UP:
            if(buffer.hasPrevious())
            {
                clearLine();
                buffer.setPrevious();
                output << buffer.getData();
            }
            break;
        case ControlSequence::Type::ARROW_DOWN:
            if(buffer.hasNext())
            {
                clearLine();
                buffer.setNext();
                output << buffer.getData();
            }
            break;
        default:
            return false;
    }

    return true;
}

void InputController::moveHome()
{
    auto times = buffer.moveCursorHome();
    output << cursorLeft(times);
}

void InputController::moveEnd()
{
    auto times = buffer.moveCursorEnd();
    output << cursorRight(times);
}