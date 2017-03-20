#pragma once

#include "quants_date/detail/schedule_type.h"
#include "quants_date/schedule.h"
#include "quants_date/scheduler/modifier_expression.h"
#include "quants_date/scheduler/detail/date_unwrapper.h"

namespace qd { namespace scheduler {
    template <typename D>
    class date_adder
        : public modifier_expression<date_adder<D>> {
        friend class modifier_expression<date_adder<D>>;
    public:
        using type = qd::detail::schedule_type<D>;

        using inner_date_type = typename type::inner_date_type;
        using container_type = typename type::container_type;

    public:
        date_adder(const inner_date_type& date);

    private:
        void do_apply(container_type& data) const;

    private:
        inner_date_type _date;
    };

    template<typename D>
    inline date_adder<D>::date_adder(const inner_date_type& date)
        : _date(date)
    {
    }

    template<typename D>
    inline void date_adder<D>::do_apply(container_type& data) const
    {
        data.emplace(_date);
    }
}}

namespace qd {
    template<typename D>
    void add(schedule<D>& to, const D& d)
    {
        const scheduler::date_adder<D> adder(d);
        to.accept(adder);
        return;
    }

    template<typename D>
    void add(schedule<D>& to, const date<D>& d)
    {
        const scheduler::detail::date_unwrapper<D> holder;
        d.accept(holder);
        add(to, holder.get());
        return;
    }
}