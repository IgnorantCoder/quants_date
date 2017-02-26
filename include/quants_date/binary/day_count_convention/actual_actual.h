#pragma once

#include <cstddef>

#include "quants_date/unary/detail/is_leap_year_impl.h"
#include "quants_date/binary/fwd.h"
#include "quants_date/binary/detail/count_days_impl.h"
#include "quants_date/binary/day_count_convention/day_count_convention_expression.h"

namespace qd { namespace binary { namespace dcc {
    class actual_actual
        : public day_count_convention_expression<actual_actual> {
        friend class day_count_fraction<actual_actual>;

    private:
        static constexpr double leap_year_coeffcient = 1. / 366.;
        static constexpr double noleap_year_coeffcient = 1. / 365.;

    public:
        actual_actual();
        actual_actual(const actual_actual& other);

    private:
        double calculate_day_count(
            const std::size_t from_y,
            const std::size_t from_m,
            const std::size_t from_d,
            const std::size_t to_y,
            const std::size_t to_m,
            const std::size_t to_d) const;
    };

    inline actual_actual::actual_actual()
    {
    }

    inline actual_actual::actual_actual(const actual_actual& other)
    {
    }

    inline double actual_actual::calculate_day_count(
        const std::size_t from_y, 
        const std::size_t from_m, 
        const std::size_t from_d, 
        const std::size_t to_y, 
        const std::size_t to_m, 
        const std::size_t to_d) const
    {
        const int diff_y
            = (static_cast<const int>(to_y) - 1)
            - (static_cast<const int>(from_y) + 1)
            + 1;

        const int from_odd
            = binary::detail::count_days_impl(
                from_y, from_m, from_d,
                from_y, 12, 31)
            + 1;
        const double from_year_coeffcient
            = unary::detail::is_leap_year_impl(from_y)
            ? leap_year_coeffcient
            : noleap_year_coeffcient;

        const int to_odd
            = binary::detail::count_days_impl(
                to_y, 1, 1,
                to_y, to_m, to_d)
            + 1;
        const double to_year_coeffcient
            = unary::detail::is_leap_year_impl(to_y)
            ? leap_year_coeffcient
            : noleap_year_coeffcient;

        return diff_y
            + from_odd * from_year_coeffcient
            + to_odd * to_year_coeffcient;
    }
}}}