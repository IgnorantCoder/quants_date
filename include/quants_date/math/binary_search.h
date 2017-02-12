#pragma once

#include <type_traits>

#include "quants_date/type_traits/has_call_operator.h"

namespace qd { namespace math {
    template <typename T, typename F>
    typename std::enable_if <
        type_traits::has_unary_operator<F, std::size_t>::value,
        std::size_t
    >::type
    binary_search(
        const T& x,
        const std::size_t lower,
        const std::size_t upper,
        F func)
    {
        if (upper == lower) {
            return lower;
        }

        const auto mid = (lower + upper) / 2;

        return func(mid + 1) < x
            ? binary_search(x, mid + 1, upper, func)
            : binary_search(x, lower, mid, func);
    }
}}