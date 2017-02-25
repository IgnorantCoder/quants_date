#pragma once

#include <cstddef>

#include "quants_date/date_range.h"
#include "quants_date/binary/binary_expression.h"
#include "quants_date/binary/detail/count_days_impl.h"

namespace qd { namespace binary {
    class days_counter : public binary_expression<days_counter> {
    private:
        using base_type = binary_expression<days_counter>;
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

    typename days_counter::result_type days_counter::get() const
    {
        return _result;
    }

    void days_counter::do_apply(
        const std::size_t from_y,
        const std::size_t from_m,
        const std::size_t from_d,
        const std::size_t to_y,
        const std::size_t to_m,
        const std::size_t to_d) const
    {
        this->_result
            = detail::count_days_impl(
                from_y, from_m, from_d,
                to_y, to_m, to_d);
    }
}}

namespace qd {
    template<typename D>
    binary::days_counter::result_type
    count_days(const date_range<D>& d)
    {
        const binary::days_counter calculator;
        d.accept(calculator);
        return calculator.get();
    }
}