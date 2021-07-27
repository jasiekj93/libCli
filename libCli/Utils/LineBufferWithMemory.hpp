#pragma once

/**
 * @file LineBufferWithMemory.hpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

#include<libCli/Utils/LineBuffer.hpp>
#include<libCli/Utils/StringCircularLifo.hpp>

namespace Cli::Utils
{
    class LineBufferWithMemory : public LineBuffer
    {
    public:
        LineBufferWithMemory(size_t size, size_t depth);
        ~LineBufferWithMemory();

        bool SetPrevious();
        bool SetNext();
        void SetCurrent();

        bool HasNext();
        bool HasPrevious();

        void ClearAndMemorize();

        inline auto MemoryCount() const { return _lifo.Count(); }
        inline auto ClearMemory() { _lifo.Clear(); }

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