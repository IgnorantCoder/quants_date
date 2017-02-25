#pragma once

#include "quants_date/unary/add_day.h"

namespace qd { namespace unary {
    template <typename D>
    class week_adder : public unary_expression<week_adder<D>> {
    private:
        using base_type = unary_expression<week_adder>;
        friend class base_type;

    public:
        using result_type = typename day_adder<D>::result_type;

    public:
        week_adder(const int n);
        result_type get() const;

    private:
        void do_apply(
            const std::size_t y,
            const std::size_t m,
            const std::size_t d) const;

    private:
        day_adder<D> _day_adder;
    };

    template<typename D>
    inline week_adder<D>::week_adder(const int n)
        : _day_adder(7 * n)
    {
    }

    template<typename D>
    inline typename week_adder<D>::result_type week_adder<D>::get() const
    {
        return this->_day_adder.get();
    }

    template<typename D>
    inline void week_adder<D>::do_apply(
        const std::size_t y,
        const std::size_t m, 
        const std::size_t d) const
    {
        this->_day_adder.apply(y, m, d);
        return;
    }
}}

namespace qd {
    template<typename D>
    typename unary::week_adder<D>::result_type
    add_week(const date<D>& d, const int n)
    {
        const unary::week_adder<D> calculator(n);
        d.accept(calculator);
        return calculator.get();
    }
}