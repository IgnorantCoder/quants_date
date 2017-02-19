#pragma once

#include <cstddef>

#include "quants_date/date_range.h"
#include "quants_date/unary/detail/the_sum_of_days_data.h"
#include "quants_date/binary/binary_expression.h"

namespace qd { namespace binary {
    class day_counter : public binary_expression<day_counter> {
    private:
        using base_type = binary_expression<day_counter>;
        friend class base_type;

    public:
        using result_type = int;

    public:
        result_type get() const;

    private:
        void do_apply(
            const std::size_t from_y,
            const std::size_t from_m,
            const std::size_t from_d,
            const std::size_t to_y,
            const std::size_t to_m,
            const std::size_t to_d) const;

    private:
        mutable result_type _result;
    };

    typename day_counter::result_type day_counter::get() const
    {
        return _result;
    }

    void day_counter::do_apply(
        const std::size_t from_y,
        const std::size_t from_m,
        const std::size_t from_d,
        const std::size_t to_y,
        const std::size_t to_m,
        const std::size_t to_d) const
    {
        const auto x0
            = unary::detail::to_serial_value_impl(from_y, from_m, from_d);
        const auto x1
            = unary::detail::to_serial_value_impl(to_y, to_m, to_d);

        this->_result
            = static_cast<int>(x1) - static_cast<int>(x0);
    }
}}

namespace qd {
    template<typename D>
    binary::day_counter::result_type
    count_day(const date_range<D>& d)
    {
        const binary::day_counter calculator;
        d.accept(calculator);
        return calculator.get();
    }

    template<typename D>
    binary::day_counter::result_type
    count_day(const date<D>& from, const date<D>& to)
    {
        return count_day(date_range<D>(from, to));
    }
}