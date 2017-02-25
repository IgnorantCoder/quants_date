#pragma once

#include <cstddef>

#include "quants_date/unary/detail/is_leap_year_impl.h"
#include "quants_date/binary/detail/count_days_impl.h"
#include "quants_date/binary/day_count_convention/day_count_convention_expression.h"

namespace qd { namespace binary { namespace dcc {
    class actual_360 : public day_count_convention_expression<actual_360> {
    private:
        static constexpr double coeffcient = 1. / 360.;

    public:
        actual_360();
        actual_360(const actual_360& other);

    public:
        double calculate_day_count(
            const std::size_t from_y,
            const std::size_t from_m,
            const std::size_t from_d,
            const std::size_t to_y,
            const std::size_t to_m,
            const std::size_t to_d) const;
    };

    inline actual_360::actual_360()
    {
    }

    inline actual_360::actual_360(const actual_360& other)
    {
    }

    inline double actual_360::calculate_day_count(
        const std::size_t from_y, 
        const std::size_t from_m, 
        const std::size_t from_d, 
        const std::size_t to_y, 
        const std::size_t to_m, 
        const std::size_t to_d) const
    {
        const double numerator
            = detail::count_days_impl(from_y, from_m, from_d, to_y, to_m, to_d);
        return numerator * coeffcient;
    }
}}}