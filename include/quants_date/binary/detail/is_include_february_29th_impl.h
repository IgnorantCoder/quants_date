#pragma once

#include <cstddef>

#include "quants_date/unary/detail/next_february_29th_impl.h"
#include "quants_date/unary/detail/the_sum_of_days_data.h"

namespace qd { namespace binary { namespace detail {
    bool is_include_february_29th_impl(
        const std::size_t from_y,
        const std::size_t from_m,
        const std::size_t from_d,
        const std::size_t to_y,
        const std::size_t to_m,
        const std::size_t to_d)
    {
        if (from_m == 2 && from_d == 29) {
            return true;
        }

        const std::size_t next_february_29th
            = unary::detail::next_february_29th_impl(from_y, from_m, from_d);
        const auto to
            = unary::detail::to_serial_value_impl(to_y, to_m, to_d);

        return next_february_29th <= to;
    }
}}}