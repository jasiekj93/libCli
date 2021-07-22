#pragma once

#include <cstddef>

namespace Terminal
{
    template <typename T>
    struct Span
    {
        const T *data;
        size_t size;
    };
    
    using CharSpan = Span<char>;
}