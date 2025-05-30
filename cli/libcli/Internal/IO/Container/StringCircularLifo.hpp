#pragma once

/**
 * @file StringCircularLifo.hpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

#include <cstddef>

namespace cli::Internal::IO::Container
{
    class StringCircularLifo
    {
    public:
        StringCircularLifo(size_t size, size_t depth);
        ~StringCircularLifo();

        bool Push(const char *);
        const char * Get(size_t) const;
        void Clear();

        inline auto Count() const { return _count; }
    
    private:
        const size_t _size;
        const size_t _depth;

        char **_data;
        int _cursor;
        size_t _count;

        StringCircularLifo(const StringCircularLifo &) = delete;
        auto operator=(const StringCircularLifo &) = delete;
    };
};