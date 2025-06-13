#include "StringStream.hpp"

using namespace cli;

void StringStream::write(char c)
{
    buffer.push_back(c);
}

void StringStream::write(etl::string_view str)
{
    buffer.insert(buffer.end(), str.begin(), str.end());
}

size_t StringStream::size() const
{
    return buffer.size();
}

void StringStream::clear()
{
    buffer.clear();
    seekg(0);
}

bool StringStream::readFrom(char& c, size_t position)
{
    if (position >= buffer.size())
        return false;

    c = buffer[position];
    return true;
   
}

bool StringStream::readFrom(etl::istring& str, size_t count, size_t position)
{
    if((position + count) > buffer.size())
        return false;

    if(str.available() < count)
        return false;

    auto begin = etl::next(buffer.begin(), position);
    str.insert(str.end(), begin, etl::next(begin, count));
    return true;
}
