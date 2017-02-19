#pragma once

#include <tuple>

#include "quants_date/builder/date_builder.h"
#include "quants_date/unary/unary_expression.h"
#include "quants_date/unary/to_serial_value.h"

namespace qd { namespace unary {
    template <typename D>
    class day_adder : public unary_expression<day_adder<D>> {
    private:
        using base_type = unary_expression<day_adder>;
        friend class base_type;

    public:
        using result_type = date<D>;

    public:
        day_adder(const int n);
        result_type get() const;

    private:
        void do_apply(
            const std::size_t y,
            const std::size_t m,
            const std::size_t d) const;

    private:
        int _n;
        mutable result_type _result;
    };

    template<typename D>
    inline day_adder<D>::day_adder(const int n)
        : _n(n),
        _result(create_date<D>())
    {
    }

    template<typename D>
    inline typename day_adder<D>::result_type day_adder<D>::get() const
    {
        return _result;
    }

    template<typename D>
    inline void day_adder<D>::do_apply(
        const std::size_t y,
        const std::size_t m,
        const std::size_t d) const
    {
        const auto val = detail::to_serial_value_impl(y, m, d);
        this->_result = create_date<D>(val + this->_n);
        return;
    }
}}

namespace qd {
    template<typename D>
    typename unary::day_adder<D>::result_type
    add_day(const date<D>& d, const int n)
    {
        const unary::day_adder<D> calculator(n);
        d.accept(calculator);
        return calculator.get();
    }
}