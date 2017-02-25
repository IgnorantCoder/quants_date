#pragma once

#include <cstddef>

#include "quants_date/unary/detail/the_number_of_days_data.h"

namespace qd { namespace unary { namespace detail {
    bool is_last_day_of_month_impl(
        const std::size_t y,
        const std::size_t m,
        const std::size_t d)
    {
        const std::size_t last_day_of_month
            = last_day_of_month_impl(y, m);
        return d == last_day_of_month;
    }
}}}