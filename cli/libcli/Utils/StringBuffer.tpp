#pragma once

namespace cli::Utils
{
        template<size_t SIZE>
        StringBuffer<SIZE>::StringBuffer()
        {
            Buffer<char, SIZE + 1>::_data[0] = '\0';
        }

        template<size_t SIZE>
        bool StringBuffer<SIZE>::Put(const char &c)
        {
            if(Buffer<char, SIZE + 1>::_count == SIZE)
                return false;

            Buffer<char, SIZE + 1>::_data[Buffer<char, SIZE + 1>::_count++] = c;
            Buffer<char, SIZE + 1>::_data[Buffer<char, SIZE + 1>::_count] = '\0';
            return true;
        }
}