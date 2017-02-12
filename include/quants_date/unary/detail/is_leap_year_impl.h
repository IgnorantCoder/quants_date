#pragma once

#include <cstddef>

#include "quants_date/math/is_multiple_of.h"

namespace qd { namespace unary { namespace detail {
    bool is_leap_year_impl(const std::size_t y)
    {
        if (math::is_multiple_of<400>(y)) {
            return true;
        }
        if (math::is_multiple_of<100>(y)) {
            return false;
        }

        return  math::is_multiple_of<4>(y);
    }
}}}