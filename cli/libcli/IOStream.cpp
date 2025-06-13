#include "IOStream.hpp"

using namespace cli;

OutputStream& OutputStream::operator<<(char c)
{
    write(c);
    return *this;
}

OutputStream& OutputStream::operator<<(etl::string_view str)
{
    write(str);
    return *this;
}

OutputStream& OutputStream::operator<<(const formatspec::Base& format)
{
    switch (format.type) 
    {
    case formatspec::Type::NEW_LINE:
        write("\r\n");
        flush();
        break;
    case formatspec::Type::CLEAR_SCREEN:
        write('\f');
        flush();
        break;
    case formatspec::Type::FLUSH:
        flush();
        break;
    
    default:
        break;
    }

    return *this;
}


InputStream::InputStream()
    : position(0)
{
}

InputStream& InputStream::operator>>(char& c)
{
    read(c);
    return *this;
}

InputStream& InputStream::operator>>(etl::istring& str)
{
    auto readSize = (str.available() < size()) ? str.available() : size();

    read(str, readSize);
    return *this;
}

bool InputStream::seekg(size_t pos)
{
    if (pos < size())
    {
        position = pos;
        return true;
    }

    return false;
}

bool InputStream::read(char& c)
{
    if (readFrom(c, position))
    {
        ++position;
        return true;
    }

    return false;
}

bool InputStream::read(etl::istring& str, size_t count)
{
    if (readFrom(str, count, position))
    {
        position += count;
        return true;
    }

    return false;
}

