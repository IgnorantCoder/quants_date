#pragma once

#include <cstddef>

#include "quants_date/unary/detail/is_leap_year_impl.h"
#include "quants_date/binary/day_count_convention/day_count_convention_expression.h"
#include "quants_date/binary/day_count_convention/pay_frequency.h"
#include "quants_date/binary/detail/count_days_impl.h"
#include "quants_date/binary/detail/is_include_february_29th_impl.h"

namespace qd { namespace binary { namespace dcc {
    template <typename F>
    struct coefficient_of_actual_365l {
        static double value(
            const std::size_t from_y,
            const std::size_t from_m,
            const std::size_t from_d,
            const std::size_t to_y,
            const std::size_t to_m,
            const std::size_t to_d)
        {
            const double dominator
                = unary::detail::is_leap_year_impl(to_y) ? 366 : 365;
            return 1. / dominator;
        }
    };

    template <>
    struct coefficient_of_actual_365l<annual> {
        static double value(
            const std::size_t from_y,
            const std::size_t from_m,
            const std::size_t from_d,
            const std::size_t to_y,
            const std::size_t to_m,
            const std::size_t to_d)
        {
            const bool is_include_february_29th
                = detail::is_include_february_29th_impl(
                    from_y, from_m, from_d,
                    to_y, to_m, to_d);
            const double dominator
                = is_include_february_29th ? 366 : 365;
            return 1. / dominator;
        }
    };

    template <typename F>
    class actual_365l 
        : public day_count_convention_expression<actual_365l<F>> {
    public:
        using frequency_type = F;

    private:
        static_assert(
            is_pay_frequency<frequency_type>::value,
            "F must be frequency_type");
    public:
        actual_365l();
        actual_365l(const actual_365l& other);

    public:
        double calculate_day_count(
            const std::size_t from_y,
            const std::size_t from_m,
            const std::size_t from_d,
            const std::size_t to_y,
            const std::size_t to_m,
            const std::size_t to_d) const;
    };

    template<typename F>
    inline actual_365l<F>::actual_365l()
    {
    }

    template<typename F>
    inline actual_365l<F>::actual_365l(const actual_365l<F>& other)
    {
    }

    template<typename F>
    inline double actual_365l<F>::calculate_day_count(
        const std::size_t from_y, 
        const std::size_t from_m,
        const std::size_t from_d, 
        const std::size_t to_y, 
        const std::size_t to_m, 
        const std::size_t to_d) const
    {
        const double numerator
            = detail::count_days_impl(from_y, from_m, from_d, to_y, to_m, to_d);
        const double coeffcient
            = coefficient_of_actual_365l<frequency_type>::value(
                from_y, from_m, from_d, to_y, to_m, to_d);
        return numerator * coeffcient;
    }
}}}