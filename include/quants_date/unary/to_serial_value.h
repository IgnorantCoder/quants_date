#pragma once

#include <utility>

#include "quants_date/date.h"
#include "quants_date/math/binary_search.h"
#include "quants_date/unary/unary_expression.h"
#include "quants_date/unary/detail/the_number_of_accumulate_days_data.h"

namespace qd { namespace unary {
    class serial_value_calculator
        : public unary_expression<serial_value_calculator> {
    private:
        using base_type = unary_expression<serial_value_calculator>;
        friend class base_type;

    public:
        using result_type = std::size_t;

    public:
        serial_value_calculator();
        result_type get() const;

    private:
        void do_apply(
            const std::size_t y,
            const std::size_t m,
            const std::size_t d) const;

    private:
        mutable result_type _result;
    };

    serial_value_calculator::serial_value_calculator()
        : _result()
    {
    }

    serial_value_calculator::result_type
    serial_value_calculator::get() const
    {
        return this->_result;
    }

    void serial_value_calculator::do_apply(
        const std::size_t y,
        const std::size_t m,
        const std::size_t d) const
    {
        this->_result = detail::to_serial_value_impl(y, m, d);
    }
}}

namespace qd {
    template<typename D>
    typename unary::serial_value_calculator::result_type
    to_serial_value(const date<D>& d)
    {
        const unary::serial_value_calculator calculator;
        d.accept(calculator);
        return calculator.get();
    }
}