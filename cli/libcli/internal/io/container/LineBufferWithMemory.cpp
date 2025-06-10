#include "LineBufferWithMemory.hpp"
#include <cstring>

using namespace cli::internal::io::container;

LineBufferWithMemory::LineBufferWithMemory()
    : LineBuffer()
    , cursor(memory.begin())
{
}

bool LineBufferWithMemory::setPrevious()
{
    if(cursor == memory.begin())
        return false;
    
    if(cursor == memory.end())
        this->copyTo(currentData);
    
    cursor--;
    this->copyFrom(*cursor);
    return true;
}

bool LineBufferWithMemory::setNext()
{
    if (cursor == memory.end())
        return false;

    cursor++;
    if (cursor == memory.end())
        this->copyFrom(currentData);
    else
        this->copyFrom(*cursor);

    return true;
}

void LineBufferWithMemory::setCurrent()
{
    cursor = memory.end();
    this->copyFrom(currentData);
}

bool LineBufferWithMemory::hasPrevious()
{
    return (cursor > memory.begin());
}

bool LineBufferWithMemory::hasNext()
{
    return (cursor < memory.end());
}

void LineBufferWithMemory::clearAndMemorize()
{
    if(memory.full())
        memory.pop_front();

    if(memory.empty() or (this->getData() != memory[0]))
        memory.push_back(this->getData());

    cursor = memory.end();
    this->clear();
}
