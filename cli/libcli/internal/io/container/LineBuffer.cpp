#include "LineBuffer.hpp"
#include <cstring>

using namespace cli::internal::io::container;

LineBuffer::LineBuffer()
    : cursor(buffer.begin())
{
}

bool LineBuffer::push(char c)
{
    if(buffer.full())
        return false;

    if(cursor == buffer.end())
        buffer.push_back(c);
    // else
        // *cursor = c;
    else
        cursor = buffer.insert(cursor, c);

    cursor++;
    return true;
}

bool LineBuffer::push(etl::string_view string)
{
    if (buffer.available() < string.size())
        return false;

    buffer.insert(cursor, string.begin(), string.end());
    cursor += string.size();
    return true;
}

void LineBuffer::clear()
{
    buffer.clear();
    cursor = buffer.begin();
}

bool LineBuffer::moveCursorLeft()
{
    if (cursor == buffer.begin())
        return false;

    cursor--;
    return true;
}

bool LineBuffer::moveCursorRight()
{
    if (cursor == buffer.end())
        return false;

    cursor++;
    return true;
}

// unsigned int LineBuffer::moveCursorMaxLeft()
// {
//     auto times = etl::distance(buffer.begin(), cursor);

//     if(times > MAX_CURSOR_MOVE_SIZE)
//         times = MAX_CURSOR_MOVE_SIZE;

//     cursor -= times;
//     return times;
// }

// unsigned int LineBuffer::moveCursorMaxRight()
// {
//     auto times = etl::distance(cursor, buffer.end());
    
//     if(times > MAX_CURSOR_MOVE_SIZE)
//         times = MAX_CURSOR_MOVE_SIZE;

//     cursor += times;
//     return times;
// }

size_t LineBuffer::moveCursorHome()
{
    auto result = etl::distance(buffer.begin(), cursor);
    cursor = buffer.begin();
    return result;
}

size_t LineBuffer::moveCursorEnd()
{
    auto result = etl::distance(cursor, buffer.end());
    cursor = buffer.end();
    return result;
}

bool LineBuffer::remove()
{
    if (cursor == buffer.end())
        return false;

    buffer.erase(cursor);
    return true;
}

etl::string_view LineBuffer::getDataAfterCursor() const
{
    return etl::string_view(cursor, buffer.end());
}

void LineBuffer::copyTo(etl::istring &output) const
{
    output = buffer;
}

void LineBuffer::copyFrom(const etl::istring& input)
{
    if(buffer.max_size() < input.size())
        return;

    buffer = input;
    cursor = buffer.end();
}