#pragma once

#include <cstddef>

#include "quants_date/date.h"
#include "quants_date/unary/to_serial_value.h"
#include "quants_date/unary/detail/the_sum_of_days_data.h"
#include "quants_date/unary/detail/is_leap_year_impl.h"
#include "quants_date/binary/detail/count_days_impl.h"
#include "quants_date/binary/day_count_convention/day_count_convention_expression.h"
#include "quants_date/binary/day_count_convention/pay_frequency.h"

namespace qd { namespace binary { namespace dcc {
    template <typename D, typename F>
    class actual_actual_icma 
        : public day_count_convention_expression<actual_actual_icma<D, F>> {
    public:
        using inner_date_type = D;
        using frequency_type = F;

    private:
        static_assert(
            is_pay_frequency<frequency_type>::value,
            "F must be frequency_type");

    public:
        actual_actual_icma(const date<inner_date_type>& payment_date);
        actual_actual_icma(const actual_actual_icma& other);

    public:
        double calculate_day_count(
            const std::size_t from_y,
            const std::size_t from_m,
            const std::size_t from_d,
            const std::size_t to_y,
            const std::size_t to_m,
            const std::size_t to_d) const;

    private:
        date<inner_date_type> _payment_date;
    };

    template<typename D, typename F>
    inline actual_actual_icma<D, F>::actual_actual_icma(
        const date<inner_date_type>& payment_date)
        : _payment_date(payment_date)
    {
    }

    template<typename D, typename F>
    inline actual_actual_icma<D, F>::actual_actual_icma(
        const actual_actual_icma & other)
        : _payment_date(other._payment_date)
    {
    }

    template<typename D, typename F>
    inline double actual_actual_icma<D, F>::calculate_day_count(
        const std::size_t from_y, 
        const std::size_t from_m, 
        const std::size_t from_d, 
        const std::size_t to_y,
        const std::size_t to_m,
        const std::size_t to_d) const
    {
        const double numerator
            = detail::count_days_impl(from_y, from_m, from_d, to_y, to_m, to_d);
        const double dominator
            = to_serial_value(this->_payment_date)
            - unary::detail::to_serial_value_impl(from_y, from_m, from_d);
        return (numerator / dominator) * frequency_type::coupon_factor;
    }
}}}