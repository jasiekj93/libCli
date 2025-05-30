#include "LineBufferWithMemory.hpp"
#include <cstring>

using namespace cli::internal::io::container;

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
    if((_lifo.Count() == 0) ||
        (std::strcmp(this->Data(), _lifo.Get(0)) != 0))
        _lifo.Push(this->Data());

    _index = 0;
    this->Clear();
}
