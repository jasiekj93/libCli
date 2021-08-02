#include "LineBufferWithMemory.hpp"

using namespace Cli::Internal::IO::Container;

LineBufferWithMemory::LineBufferWithMemory(size_t size, size_t depth)
    : LineBuffer(size)
    , _size(size)
    , _depth(depth)
    , _lifo(size, depth)
    , _index(0)
{
    _currentData = new char[_size + 1];
}

LineBufferWithMemory::~LineBufferWithMemory()
{
    delete[] _currentData;
}

bool LineBufferWithMemory::SetPrevious()
{
    if (_index == _depth)
        return false;

    if (_index >= _lifo.Count())
        return false;

    if (_index == 0)
        this->_CopyTo(_currentData);

    _index++;
    this->_CopyFrom(_lifo.Get(_index - 1));

    return true;
}

bool LineBufferWithMemory::SetNext()
{
    if (_index == 0)
        return false;

    _index--;
    if (_index == 0)
        this->_CopyFrom(_currentData);
    else
        this->_CopyFrom(_lifo.Get(_index - 1));

    return true;
}

void LineBufferWithMemory::SetCurrent()
{
    _index = 0;
    this->_CopyFrom(_currentData);
}

bool LineBufferWithMemory::HasNext()
{
    return (_index > 0);
}

bool LineBufferWithMemory::HasPrevious()
{
    return (_index < _depth);
}

void LineBufferWithMemory::ClearAndMemorize()
{
    _lifo.Push(this->Data());
    _index = 0;
    this->Clear();
}
