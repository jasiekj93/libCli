#include "OutputStreamLarge.hpp"
#include <cstring>

using namespace mock;

void OutputStreamLarge::write(char c)
{
    if (line.size() < SIZE)
        line.push_back(c);
}

void OutputStreamLarge::write(etl::string_view string)
{
    if(line.available() >= string.size())
        line.insert(line.end(), string.begin(), string.end());
}
