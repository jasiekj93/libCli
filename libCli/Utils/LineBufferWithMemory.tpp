#pragma once

namespace Cli::Utils
{
    template <size_t DEPTH, size_t SIZE>
    LineBufferWithMemory<DEPTH, SIZE>::LineBufferWithMemory()
        : _index(0)
    {
    }

    template <size_t DEPTH, size_t SIZE>
    bool LineBufferWithMemory<DEPTH, SIZE>::SetPrevious()
    {
        if(_index == DEPTH)
            return false;

        if(_index >= _lifo.Count())
            return false;

        if(_index == 0)
            this->_CopyTo(_currentData); 

        _index++;
        this->_CopyFrom(_lifo.Get(_index - 1));
        
        return true;
    }

    template <size_t DEPTH, size_t SIZE>
    bool LineBufferWithMemory<DEPTH, SIZE>::SetNext()
    {
        if(_index == 0)
            return false;

        _index--;
        if(_index == 0)
            this->_CopyFrom(_currentData);
        else
            this->_CopyFrom(_lifo.Get(_index - 1));

        return true;
    }

    template <size_t DEPTH, size_t SIZE>
    void LineBufferWithMemory<DEPTH, SIZE>::SetCurrent()
    {
        _index = 0;
        this->_CopyFrom(_currentData);
    }

    template <size_t DEPTH, size_t SIZE>
    void LineBufferWithMemory<DEPTH, SIZE>::ClearAndMemorize()
    {
        _lifo.Push(this->Data());
        _index = 0;
        this->Clear();
    }
}