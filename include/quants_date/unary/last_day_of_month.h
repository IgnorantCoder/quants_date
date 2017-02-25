#pragma once

#include "quants_date/date.h"
#include "quants_date/unary/unary_expression.h"
#include "quants_date/unary/detail/the_number_of_days_data.h"

namespace qd { namespace unary {
    class last_day_of_month_calculator 
        : public unary_expression<last_day_of_month_calculator> {
    private:
        using base_type = unary_expression<last_day_of_month_calculator>;
        friend class base_type;

    public:
        using result_type = std::size_t;

    public:
        last_day_of_month_calculator();
        result_type get() const;

    private:
        void do_apply(
            const std::size_t y,
            const std::size_t m,
            const std::size_t /*d*/) const;

    private:
        mutable result_type _result;
    };

    last_day_of_month_calculator::last_day_of_month_calculator()
        : _result()
    {
    }

    last_day_of_month_calculator::result_type 
    last_day_of_month_calculator::get() const
    {
        return this->_result;
    }

    void last_day_of_month_calculator::do_apply(
        const std::size_t y, 
        const std::size_t m,
        const std::size_t /*d*/) const
    {
        this->_result = detail::last_day_of_month_impl(y, m);
    }
}}

namespace qd {
    template<typename D>
    typename unary::last_day_of_month_calculator::result_type
    last_day_of_month(const date<D>& d)
    {
        const unary::last_day_of_month_calculator calculator;
        d.accept(calculator);
        return calculator.get();
    }
}