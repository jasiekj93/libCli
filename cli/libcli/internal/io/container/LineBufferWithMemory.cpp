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

bool LineBufferWithMemory::setPrevious()
{
    if (_index == _depth)
        return false;

    if (_index >= _lifo.count())
        return false;

    if (_index == 0)
        this->copyTo(_currentData);

    _index++;
    this->copyFrom(_lifo.get(_index - 1));

    return true;
}

bool LineBufferWithMemory::setNext()
{
    if (_index == 0)
        return false;

    _index--;
    if (_index == 0)
        this->copyFrom(_currentData);
    else
        this->copyFrom(_lifo.get(_index - 1));

    return true;
}

void LineBufferWithMemory::setCurrent()
{
    _index = 0;
    this->copyFrom(_currentData);
}

bool LineBufferWithMemory::hasNext()
{
    return (_index > 0);
}

bool LineBufferWithMemory::hasPrevious()
{
    return (_index < _depth);
}

void LineBufferWithMemory::clearAndMemorize()
{
    if((_lifo.count() == 0) ||
        (std::strcmp(this->data(), _lifo.get(0)) != 0))
        _lifo.push(this->data());

    _index = 0;
    this->clear();
}
