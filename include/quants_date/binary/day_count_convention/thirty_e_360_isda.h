#pragma once

#include <algorithm>
#include <cstddef>

#include "quants_date/date.h"
#include "quants_date/unary/to_serial_value.h"
#include "quants_date/unary/is_last_day_of_month.h"
#include "quants_date/unary/detail/the_sum_of_days_data.h"
#include "quants_date/binary/fwd.h"
#include "quants_date/binary/day_count_convention/day_count_convention_expression.h"

namespace qd { namespace binary { namespace dcc {
    class thirty_e_360_isda 
        : public day_count_convention_expression<thirty_e_360_isda> {
        friend class day_count_fraction<thirty_e_360_isda>;

    public:
        template <typename D>
        thirty_e_360_isda(const date<D>& maturity_date);
        thirty_e_360_isda(const thirty_e_360_isda& other);

    private:
        double calculate_day_count(
            const std::size_t from_y,
            const std::size_t from_m,
            const std::size_t from_d,
            const std::size_t to_y,
            const std::size_t to_m,
            const std::size_t to_d) const;

    private:
        std::size_t _serial_value_of_maturity_date;
    };

    template <typename D>
    inline thirty_e_360_isda::thirty_e_360_isda(
        const date<D>& maturity_date)
        : _serial_value_of_maturity_date(to_serial_value(maturity_date))
    {
    }

    inline thirty_e_360_isda::thirty_e_360_isda(
        const thirty_e_360_isda& other)
        : _serial_value_of_maturity_date(other._serial_value_of_maturity_date)
    {
    }

    inline double thirty_e_360_isda::calculate_day_count(
        const std::size_t from_y, 
        const std::size_t from_m,
        const std::size_t from_d,
        const std::size_t to_y,
        const std::size_t to_m,
        const std::size_t to_d) const
    {
        const int y = static_cast<int>(to_y) - static_cast<int>(from_y);
        const int m = static_cast<int>(to_m) - static_cast<int>(from_m);

        const int adjusted_from_d 
            = unary::detail::is_last_day_of_month_impl(from_y, from_m, from_d)
            ? 30
            : from_d;
        const auto serial_value_of_to_date
            = unary::detail::to_serial_value_impl(to_y, to_m, to_d);
        const bool is_to_date_maturity_date
            = this->_serial_value_of_maturity_date == serial_value_of_to_date;
        const bool is_to_date_february
            = (to_m == 2);
        const int adjusted_to_d
            = unary::detail::is_last_day_of_month_impl(to_y, to_m, to_d)
            ? is_to_date_maturity_date || is_to_date_february
                ? to_d
                : 30
            : to_d;
        const int d = adjusted_to_d - adjusted_from_d;

        return y + m / 12. + d / 360.;
    }
}}}