#pragma once

#include <cstddef>

namespace Cli
{
    template <typename T>
    struct Span
    {
        const T *data;
        size_t size;
    };
    
    using CharSpan = Span<char>;
}