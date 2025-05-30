#pragma once

/**
 * @file Dictionary.hpp
 * @author Adrian Szczepanski
 * @date 16-09-2021
 * @brief 
 * @details
 */

#include <libcli/utils/Buffer.hpp>

namespace cli::utils
{
    template<class T, size_t SIZE>
    class Dictionary : public Buffer<T, SIZE>
    {
    public:
        bool Put(const T &) override;

        bool Contains(const char *) const;
        int At(const char *) const;
        T Get(const char *) const;
    };
}

#include <libcli/utils/Dictionary.tpp>