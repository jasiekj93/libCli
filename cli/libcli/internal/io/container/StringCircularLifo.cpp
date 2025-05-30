#include "StringCircularLifo.hpp"
#include <cstring>

using namespace cli::internal::io::container;

StringCircularLifo::StringCircularLifo(size_t size, size_t depth)
    : _size(size)
    , _depth(depth)
{
    _data = new char*[_depth];

    for(size_t i = 0; i < _depth; i++)
        _data[i] = new char[_size + 1];

    Clear();
}

StringCircularLifo::~StringCircularLifo()
{
    for(size_t i = 0; i < _depth; i++)
        delete[] _data[i];

    delete[] _data;
}

bool StringCircularLifo::Push(const char *string)
{
    if (std::strlen(string) > _size)
        return false;

    std::strcpy(_data[_cursor], string);

    _cursor = (_cursor + 1) % _depth;

    if (_count < _depth)
        _count++;

    return true;
}

const char * StringCircularLifo::Get(size_t id) const
{
    if (id >= _count)
        return nullptr;

    int index = (_cursor - 1) - (int)id;
    if (index < 0)
        index = _depth + index;

    return _data[index];
}

void StringCircularLifo::Clear()
{
    for (size_t i = 0; i < _depth; i++)
    {
        _data[i][0] = '\0';
    }
    _count = 0;
    _cursor = 0;
}
