#pragma once

#include <algorithm>

#include "quants_date/builder/date_builder.h"
#include "quants_date/unary/unary_expression.h"
#include "quants_date/unary/last_day_of_month.h"

namespace qd { namespace unary {
    template <typename D>
    class year_adder : public unary_expression<year_adder<D>> {
    private:
        using base_type = unary_expression<year_adder>;
        friend class base_type;

    public:
        using result_type = date<D>;

    public:
        year_adder(const int n);
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
    inline year_adder<D>::year_adder(const int n)
        : _n(n),
        _result(create_date<D>())
    {
    }

    template<typename D>
    inline typename year_adder<D>::result_type year_adder<D>::get() const
    {
        return _result;
    }

    template<typename D>
    inline void year_adder<D>::doApply(
        const std::size_t y,
        const std::size_t m,
        const std::size_t d) const
    {
        this->_result = create_date<D>(
            y + this->_n,
            m, 
            std::min(
                d,
                detail::the_number_of_days_data::value(
                    y + this->_n,
                    m)));
    }
}}

namespace qd {
    template<typename D>
    typename unary::year_adder<D>::result_type
    add_year(const date<D>& d, const int n)
    {
        const unary::year_adder<D> calculator(n);
        d.accept(calculator);
        return calculator.get();
    }
}