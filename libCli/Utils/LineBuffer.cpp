#include "LineBuffer.hpp"
#include <cstring>

using namespace Cli::Utils;

LineBuffer::LineBuffer(size_t size)
    : _size(size)
    , _count(0)
    , _cursor(0)
{
    _data = new char[size + 1];
}

LineBuffer::~LineBuffer()
{
    delete[] _data;
    _data = nullptr;
}


bool LineBuffer::Put(char c)
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

bool LineBuffer::PutString(const char *string)
{
    auto length = std::strlen(string);

    if ((_cursor + length + 1) == _size)
        return false;

    for (size_t i = 0; i < length; i++)
        Put(string[i]);

    return true;
}

void LineBuffer::Clear()
{
    _count = 0;
    _cursor = 0;
    _data[0] = '\0';
}

bool LineBuffer::MoveCursorLeft()
{
    if (_cursor == 0)
        return false;

    _cursor--;
    return true;
}

bool LineBuffer::MoveCursorRight()
{
    if (_cursor == _count)
        return false;

    _cursor++;
    return true;
}

bool LineBuffer::Delete()
{
    if (_cursor == _count)
        return false;

    auto size = _count - _cursor;
    std::memmove(&_data[_cursor], &_data[_cursor + 1], size);
    _count--;

    return true;
}

void LineBuffer::_CopyTo(char *output)
{
    std::strcpy(output, _data);
}

void LineBuffer::_CopyFrom(const char *input)
{
    std::strcpy(_data, input);
    _count = strlen(input);
    _cursor = _count;
}