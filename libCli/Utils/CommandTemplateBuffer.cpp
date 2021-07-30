#include "CommandTemplateBuffer.hpp"
#include <cstring>

using namespace Cli;
using namespace Cli::Utils;

CommandTemplate CommandTemplateBuffer::_empty;

bool CommandTemplateBuffer::Put(const CommandTemplate &command)
{
    if(Contains(command.Name()) == true)
        return false;
    else
        return Buffer::Put(command);
}

bool CommandTemplateBuffer::Contains(const char *name) const
{
    return (At(name) >= 0);
}

int CommandTemplateBuffer::At(const char *name) const
{
    for(size_t i = 0; i < _count; i++)
        if(std::strcmp(_data[i].Name(), name) == 0)
            return i;

    return -1;
}

const CommandTemplate & CommandTemplateBuffer::Get(const char *name) const
{
    auto at = At(name);

    if(at == -1)
        return _empty;
    else
        return _data[at];
}
