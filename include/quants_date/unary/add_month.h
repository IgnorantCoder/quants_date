#pragma once

#include <algorithm>

#include "quants_date/builder/date_builder.h"
#include "quants_date/unary/unary_expression.h"
#include "quants_date/unary/last_day_of_month.h"

namespace qd { namespace unary {
    template <typename D>
    class month_adder : public unary_expression<month_adder<D>> {
    private:
        using base_type = unary_expression<month_adder>;
        friend class base_type;

    public:
        using result_type = date<D>;

    public:
        month_adder(const int n);
        result_type get() const;

    private:
        void doApply(
            const std::size_t y,
            const std::size_t m,
            const std::size_t d) const;

    private:
        int _n;
        mutable result_type _result;
    };

    template<typename D>
    inline month_adder<D>::month_adder(const int n)
        : _n(n),
        _result(create_date<D>())
    {
    }

    template<typename D>
    inline typename month_adder<D>::result_type month_adder<D>::get() const
    {
        return _result;
    }

    template<typename D>
    inline void month_adder<D>::doApply(
        const std::size_t y,
        const std::size_t m,
        const std::size_t d) const
    {
        const auto new_y = y + this->_n / 12;
        const auto new_m = m + this->_n % 12;

        this->_result = create_date<D>(
            new_y,
            new_m,
            std::min(
                d,
                detail::the_number_of_days_data::value(
                    new_y,
                    new_m)));
    }
}}

namespace qd {
    template<typename D>
    typename unary::month_adder<D>::result_type
    add_month(const date<D>& d, const int n)
    {
        const unary::month_adder<D> calculator(n);
        d.accept(calculator);
        return calculator.get();
    }
}