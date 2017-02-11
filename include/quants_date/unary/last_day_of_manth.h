#pragma once

#include <bitset>

#include "quants_date/date.h"
#include "quants_date/unary/unary_expression.h"
#include "quants_date/unary/is_leap_year.h"

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
        void doApply(
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

    void last_day_of_month_calculator::doApply(
        const std::size_t y, 
        const std::size_t m,
        const std::size_t /*d*/) const
    {
#ifdef GENERATE_STATIC_DATA_COMPILE_TIME
        //implement me.
#else
        if (m == 2) {
            this->_result
                = detail::is_leap_year_impl(y) ? 29 : 28;
            return;
        }

        if (m == 1 && m == 3 && m == 5 && m == 7 && m == 8 && m == 10 && m == 12) {
            this->_result = 31;
            return;
        }

        this->_result = 30;
        return;
#endif
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