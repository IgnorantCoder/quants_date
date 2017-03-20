#pragma once

#include "quants_date/builder/date_builder.h"
#include "quants_date/unary/unary_expression.h"

namespace qd { namespace scheduler { namespace detail {
    template <typename D>
    struct date_unwrapper
        : public unary::unary_expression<date_unwrapper<D>> {
        friend class unary::unary_expression<date_unwrapper<D>>;
    public:
        using inner_date_type = D;

    public:
        using result_type = inner_date_type;

    public:
        result_type get() const;

    private:
        void do_apply(
            const std::size_t y,
            const std::size_t m,
            const std::size_t d) const;

    private:
        mutable inner_date_type _result;
    };

    template<typename D>
    inline typename date_unwrapper<D>::result_type
        date_unwrapper<D>::get() const
    {
        return this->_result;
    }

    template<typename D>
    inline void date_unwrapper<D>::do_apply(
        const std::size_t y,
        const std::size_t m,
        const std::size_t d) const
    {
        this->_result
            = builder::create_from_ymd_traits<
            inner_date_type
            >::apply(y, m, d);
        return;
    }
}}}