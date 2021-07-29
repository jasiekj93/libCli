#include "ArgumentBuffer.hpp"

using namespace Cli;
using namespace Cli::Utils;

Argument ArgumentBuffer::_empty;

bool ArgumentBuffer::Put(const Argument &arg)
{
    if(Contains(arg.Name()) == true)
        return false;
    else
        return Buffer::Put(arg);
}

bool ArgumentBuffer::Contains(char c) const
{
    return (At(c) != -1);
}

int ArgumentBuffer::At(char c) const
{
    for(size_t i = 0; i < _count; i++)
        if(_data[i].Name() == c)
            return i;

    return -1;
}

const Argument & ArgumentBuffer::Get(char c)
{
    auto at = At(c);

    if(at == -1)
        return _empty;
    else
        return _data[at];
}


