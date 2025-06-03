#pragma once

/**
 * @file StringCircularLifo.hpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

#include <cstddef>

namespace cli::internal::io::container
{
    class StringCircularLifo
    {
    public:
        StringCircularLifo(size_t size, size_t depth);
        ~StringCircularLifo();

        bool push(const char *);
        const char * get(size_t) const;
        void clear();

        inline auto count() const { return _count; }
    
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