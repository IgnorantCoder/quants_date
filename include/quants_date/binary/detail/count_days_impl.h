#pragma once

#include <cstddef>

#include "quants_date/unary/detail/the_sum_of_days_data.h"

namespace qd { namespace binary { namespace detail {
    int count_days_impl(
        const std::size_t from_y,
        const std::size_t from_m,
        const std::size_t from_d,
        const std::size_t to_y,
        const std::size_t to_m,
        const std::size_t to_d)
    {
        const auto x0
            = unary::detail::to_serial_value_impl(from_y, from_m, from_d);
        const auto x1
            = unary::detail::to_serial_value_impl(to_y, to_m, to_d);

        return static_cast<int>(x1) - static_cast<int>(x0);
    }
}}}