#pragma once

#include "quants_date/detail/schedule_type.h"
#include "quants_date/scheduler/modifier_expression.h"

namespace qd {
    template <typename D>
    class schedule {
    public:
        using type = detail::schedule_type<D>;
        using inner_date_type = typename type::inner_date_type;
        using container_type = typename type::container_type;

    public:
        schedule();
        schedule(const container_type& data);
        schedule(container_type&& data);

    public:
        template <typename E>
        void accept(scheduler::modifier_expression<E>& visitor);
        template <typename E>
        void accept(const scheduler::modifier_expression<E>& visitor);

    private:
        container_type _data;
    };

    template<typename D>
    inline schedule<D>::schedule()
        : _data()
    {
    }

    template<typename D>
    inline schedule<D>::schedule(const container_type & data)
        : _data(data)
    {
    }

    template<typename D>
    inline schedule<D>::schedule(container_type && data)
        : _data(std::move(data))
    {
    }

    template<typename D>
    template<typename E>
    inline void schedule<D>::accept(
        scheduler::modifier_expression<E>& visitor)
    {
        visitor.apply<inner_date_type>(_data);
        return;
    }

    template<typename D>
    template<typename E>
    inline void schedule<D>::accept(
        const scheduler::modifier_expression<E>& visitor)
    {
        visitor.apply<inner_date_type>(_data);
        return;
    }
}