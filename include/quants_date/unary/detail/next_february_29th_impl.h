#pragma once

#include <cstddef>

#include "quants_date/unary/detail/is_leap_year_impl.h"
#include "quants_date/unary/detail/the_sum_of_days_data.h"

namespace qd { namespace unary { namespace detail {
    std::size_t next_february_29th_impl(
        const std::size_t y,
        const std::size_t m,
        const std::size_t d)
    {
        if (unary::detail::is_leap_year_impl(y) && (m < 3)) {
            return unary::detail::to_serial_value_impl(y, 2, 29);
        }

        const auto next_leap_year = y + (4 - y % 4);
        return unary::detail::to_serial_value_impl(next_leap_year, 2, 29);
    }
}}}