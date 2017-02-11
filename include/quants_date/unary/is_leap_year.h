#pragma once

#include "quants_date/date.h"
#include "quants_date/math/is_multiple_of.h"
#include "quants_date/unary/unary_expression.h"

namespace qd { namespace unary {
    namespace detail {
        bool is_leap_year_impl(const std::size_t y)
        {
            if (math::is_multiple_of<400>(y)) {
                return true;
            }
            if (math::is_multiple_of<100>(y)) {
                return false;
            }

            return  math::is_multiple_of<4>(y);
        }
    }

    class leap_year_checker : public unary_expression<leap_year_checker> {
    private:
        using base_type = unary_expression<leap_year_checker>;
        friend class base_type;

    public:
        using result_type = bool;

    public:
        leap_year_checker();
        result_type get() const;

    private:
        void doApply(
            const std::size_t y,
            const std::size_t /*m*/,
            const std::size_t /*d*/) const;

    private:
        mutable result_type _result;
    };

    leap_year_checker::leap_year_checker()
        : _result(false)
    {
    }

    typename leap_year_checker::result_type
    leap_year_checker::get() const
    {
        return _result;
    }

    void leap_year_checker::doApply(
        const std::size_t y, 
        const std::size_t /*m*/, 
        const std::size_t /*d*/) const
    {
        this->_result = detail::is_leap_year_impl(y);
        return;
    }
}}

namespace qd {
    template<typename D>
    typename unary::leap_year_checker::result_type
    is_leap_year(const date<D>& d)
    {
        const unary::leap_year_checker checker;
        d.accept(checker);
        return checker.get();
    }
}