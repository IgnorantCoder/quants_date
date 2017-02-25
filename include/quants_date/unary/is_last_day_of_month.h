#pragma once

#include "quants_date/date.h"
#include "quants_date/unary/unary_expression.h"
#include "quants_date/unary/detail/is_last_day_of_month_impl.h"

namespace qd { namespace unary {
    class last_day_of_month_checker
        : public unary_expression<last_day_of_month_checker> {
    private:
        using base_type = unary_expression<last_day_of_month_checker>;
        friend class base_type;

    public:
        using result_type = bool;

    public:
        last_day_of_month_checker();
        result_type get() const;

    private:
        void do_apply(
            const std::size_t y,
            const std::size_t m,
            const std::size_t /*d*/) const;

    private:
        mutable result_type _result;
    };

    last_day_of_month_checker::last_day_of_month_checker()
        : _result()
    {
    }

    last_day_of_month_checker::result_type 
    last_day_of_month_checker::get() const
    {
        return this->_result;
    }

    void last_day_of_month_checker::do_apply(
        const std::size_t y, 
        const std::size_t m,
        const std::size_t d) const
    {
        this->_result = detail::is_last_day_of_month_impl(y, m, d);
    }
}}

namespace qd {
    template<typename D>
    typename unary::last_day_of_month_checker::result_type
    is_last_day_of_month(const date<D>& d)
    {
        const unary::last_day_of_month_checker calculator;
        d.accept(calculator);
        return calculator.get();
    }
}