#include "LineBuffer.hpp"
#include <cstring>

using namespace cli::internal::io::container;

LineBuffer::LineBuffer(size_t size)
    : _size(size)
    , _count(0)
    , _cursor(0)
{
    _data = new char[size + 1];
    _data[0] = '\0';
}

LineBuffer::~LineBuffer()
{
    delete[] _data;
    _data = nullptr;
}


bool LineBuffer::put(char c)
{
    if (_cursor == _size)
        return false;

    _data[_cursor] = c;

    if (_count == _cursor)
    {
        _count++;
        _data[_count] = '\0';
    }

    _cursor++;
    return true;
}

bool LineBuffer::putString(const char *string)
{
    auto length = std::strlen(string);

    if ((_cursor + length + 1) == _size)
        return false;

    for (size_t i = 0; i < length; i++)
        put(string[i]);

    return true;
}

void LineBuffer::clear()
{
    _count = 0;
    _cursor = 0;
    _data[0] = '\0';
}

bool LineBuffer::moveCursorLeft()
{
    if (_cursor == 0)
        return false;

    _cursor--;
    return true;
}

bool LineBuffer::moveCursorRight()
{
    if (_cursor == _count)
        return false;

    _cursor++;
    return true;
}

unsigned int LineBuffer::moveCursorMaxLeft()
{
    unsigned int times = _cursor;

    if(times > MAX_CURSOR_MOVE_SIZE)
        times = MAX_CURSOR_MOVE_SIZE;

    _cursor -= times;
    return times;
}

unsigned int LineBuffer::moveCursorMaxRight()
{
    unsigned int times = _count - _cursor;
    
    if(times > MAX_CURSOR_MOVE_SIZE)
        times = MAX_CURSOR_MOVE_SIZE;

    _cursor += times;
    return times;
}

bool LineBuffer::remove()
{
    if (_cursor == _count)
        return false;

    auto size = _count - _cursor;
    std::memmove(&_data[_cursor], &_data[_cursor + 1], size);
    _count--;

    return true;
}

void LineBuffer::copyTo(char *output) const
{
    std::strcpy(output, _data);
}

void LineBuffer::copyFrom(const char *input)
{
    std::strcpy(_data, input);
    _count = strlen(input);
    _cursor = _count;
}