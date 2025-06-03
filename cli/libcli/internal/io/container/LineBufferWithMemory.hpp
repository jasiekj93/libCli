#pragma once

/**
 * @file LineBufferWithMemory.hpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

#include <libcli/internal/io/container/LineBuffer.hpp>
#include <libcli/internal/io/container/StringCircularLifo.hpp>

namespace cli::internal::io::container
{
    class LineBufferWithMemory : public LineBuffer
    {
    public:
        LineBufferWithMemory(size_t size, size_t depth);
        ~LineBufferWithMemory();

        bool setPrevious();
        bool setNext();
        void setCurrent();

        bool hasNext();
        bool hasPrevious();

        void clearAndMemorize();

        inline auto memoryCount() const { return _lifo.count(); }
        inline auto clearMemory() { _lifo.clear(); }

    private:
        const size_t _size;
        const size_t _depth;

        char *_currentData;
        StringCircularLifo _lifo;
        size_t _index;

        LineBufferWithMemory(const LineBufferWithMemory &) = delete;
        auto operator=(const LineBufferWithMemory &) = delete;
    };
}