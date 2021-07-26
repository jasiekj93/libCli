#pragma once

/**
 * @file StringCircularLifo.hpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

#include <cstddef>

namespace Cli::Utils
{
    template<size_t SIZE, size_t DEPTH>
    class StringCircularLifo
    {
    public:
        StringCircularLifo();

        bool Push(const char *);
        const char * Get(size_t) const;
        void Clear();

        inline auto Count() const { return _count;}
    
    private:
        char _data[DEPTH][SIZE + 1];
        int _cursor;
        size_t _count;
    };
};

#include <libCli/Utils/StringCircularLifo.tpp>