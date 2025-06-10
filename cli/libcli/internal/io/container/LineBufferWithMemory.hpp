#pragma once

/**
 * @file LineBufferWithMemory.hpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

#include <etl/string.h>
#include <etl/vector.h>

#include <libcli/internal/io/container/LineBuffer.hpp>

namespace cli::internal::io::container
{
    class LineBufferWithMemory : public LineBuffer
    {
    public:
        static constexpr auto DEPTH = Configuration::MAX_HISTORY;
        static constexpr auto SIZE = Configuration::MAX_COMMAND_LENGTH;

        using Memory = etl::vector<etl::string<SIZE>, DEPTH>;

        LineBufferWithMemory();

        bool setPrevious();
        bool setNext();
        void setCurrent();

        bool hasNext();
        bool hasPrevious();

        void clearAndMemorize();

        inline auto memoryCount() const { return memory.size(); }
        inline auto clearMemory() { memory.clear(); }

    private:
        etl::string<SIZE> currentData;
        Memory memory;
        Memory::iterator cursor;
    };
}