#pragma once

namespace qd { namespace math {
    template <std::size_t N>
    bool is_multiple_of(const int x)
    {
        return x % N == 0;
    }
}}