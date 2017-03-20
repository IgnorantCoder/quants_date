#pragma once

#include "quants_date/detail/schedule_type.h"
#include "quants_date/scheduler/selector_expression.h"

namespace qd { namespace scheduler { namespace detail {
    template <typename D>
    struct schedule_unwrapper
        : public selector_expression<schedule_unwrapper<D>> {
        friend class selector_expression<schedule_unwrapper<D>>;

    public:
        using type = qd::detail::schedule_type<D>;

        using inner_date_type = typename type::inner_date_type;
        using container_type = typename type::container_type;

    public:
        using result_type = container_type;

    public:
        result_type get() const;

    private:
        void do_apply(const container_type& data) const;

    private:
        mutable container_type _data;
    };

    template<typename D>
    inline typename schedule_unwrapper<D>::result_type 
    schedule_unwrapper<D>::get() const
    {
        return _data;
    }

    template<typename D>
    inline void schedule_unwrapper<D>::do_apply(
        const container_type& data) const
    {
        this->_data = data;
    }
}}}