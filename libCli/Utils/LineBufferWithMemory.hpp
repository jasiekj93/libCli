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
    template<size_t DEPTH, size_t SIZE>
    class LineBufferWithMemory : public LineBuffer<SIZE>
    {
    public:
        LineBufferWithMemory();

        bool SetPrevious();
        bool SetNext();
        void SetCurrent();

        void ClearAndMemorize();

        inline auto MemoryCount() const { return _lifo.Count(); }
        inline auto ClearMemory() { _lifo.Clear(); }

    private:
        char _currentData[SIZE + 1];
        StringCircularLifo<SIZE, DEPTH> _lifo;
        size_t _index;
    };
}

#include <libCli/Utils/LineBufferWithMemory.tpp>