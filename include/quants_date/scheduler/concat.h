#pragma once

#include <xutility>

#include "quants_date/detail/schedule_type.h"
#include "quants_date/scheduler/modifier_expression.h"
#include "quants_date/scheduler/detail/schedule_unwrapper.h"

namespace qd { namespace scheduler {
    template <typename D, typename V>
    class schedule_concatter 
        : public modifier_expression<schedule_concatter<D, V>> {
        friend class modifier_expression<schedule_concatter<D, V>>;
    public:
        using type = qd::detail::schedule_type<D>;

        using inner_date_type = typename type::inner_date_type;
        using container_type = typename type::container_type;
        using extend_type = V;

    public:
        schedule_concatter(extend_type&& extend);

    private:
        void do_apply(container_type& data) const;

    private:
        extend_type _extend;
    };

    template<typename D, typename V>
    inline schedule_concatter<D, V>::schedule_concatter(extend_type&& extend)
        : _extend(std::move(extend))
    {
    }

    template<typename D, typename V>
    inline void schedule_concatter<D, V>::do_apply(container_type& data) const
    {
        data.insert(
            _extend.cbegin(),
            _extend.cend());
        return;
    }
}}

namespace qd {
    template<typename D>
    void concat(schedule<D>& s0, const schedule<D>& s1)
    {
        const scheduler::detail::schedule_unwrapper<D> holder;
        s1.accept(holder);

        using schedule_type = detail::schedule_type<D>;
        using concatter_type 
            = scheduler::schedule_concatter<
                typename schedule_type::inner_date_type,
                typename schedule_type::container_type
            >;
        const concatter_type concatter(std::move(holder.get()));
        s0.accept(concatter);

        return;
    }

    template<typename D>
    schedule<D> concat_copy(
        const schedule<D>& s0,
        const schedule<D>& s1)
    {
        schedule<D> tmp = s0;
        concat(tmp, s1);
        return tmp;
    }
}