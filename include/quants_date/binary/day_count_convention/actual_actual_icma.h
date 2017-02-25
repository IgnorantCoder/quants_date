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
    template <typename F>
    class actual_actual_icma 
        : public day_count_convention_expression<actual_actual_icma<F>> {
    public:
        using frequency_type = F;

    private:
        static_assert(
            is_pay_frequency<frequency_type>::value,
            "F must be frequency_type");

    public:
        template <typename D>
        actual_actual_icma(const date<D>& payment_date);
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
        std::size_t  _serial_value_of_payment_date;
    };

    template<typename F>
    template <typename D>
    inline actual_actual_icma<F>::actual_actual_icma(
        const date<D>& payment_date)
        : _serial_value_of_payment_date(unary::to_serial_value(payment_date))
    {
    }

    template<typename F>
    inline actual_actual_icma<F>::actual_actual_icma(
        const actual_actual_icma<F> & other)
        : _serial_value_of_payment_date(other._serial_value_of_payment_date)
    {
    }

    template<typename F>
    inline double actual_actual_icma<F>::calculate_day_count(
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
            = this->_serial_value_of_payment_date
            - unary::detail::to_serial_value_impl(from_y, from_m, from_d);
        const double coeffcient
            = frequency_type::coupon_factor / dominator;
        return numerator * coeffcient;
    }
}}}