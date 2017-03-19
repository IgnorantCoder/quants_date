#pragma once

#include <iterator>

#include "quants_date/detail/schedule_type.h"
#include "quants_date/scheduler/modifier_expression.h"

namespace qd { namespace scheduler {
    namespace detail {
        template <typename D>
        struct schedule_unwrapper
            : public modifier_expression<schedule_unwrapper<D>> {
            friend class modifier_expression<schedule_unwrapper<D>>;

        public:
            using type = qd::detail::schedule_type<D>;

            using inner_date_type = typename type::inner_date_type;
            using container_type = typename type::container_type;

        public:
            using result_type = container_type;

        public:
            result_type get() const;

        private:
            void do_apply(container_type& data) const;

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
            container_type & data) const
        {
            this->_data = data;
        }
    }

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
        schedule_concatter(const extend_type& extend);

    private:
        void do_apply(container_type& data) const;

    private:
        extend_type _extend;
    };

    template<typename D, typename V>
    inline schedule_concatter<D, V>::schedule_concatter(
        extend_type&& extend)
        : _extend(std::move(extend))
    {
    }

    template<typename D, typename V>
    inline schedule_concatter<D, V>::schedule_concatter(
        const extend_type& extend)
        : _extend(extend)
    {
    }

    template<typename D, typename V>
    inline void schedule_concatter<D, V>::do_apply(container_type & data) const
    {
        data.insert(std::begin(_extend), std::end(_extend));
        return;
    }
}}

namespace qd {
    template<typename D, typename V>
    void concat(schedule<D>& to, const V& data)
    {
        const scheduler::schedule_concatter<D, V> conctter(data);
        to.accept(conctter);
        return;
    }

    template<typename D>
    void concat(schedule<D>& s0, schedule<D>& s1)
    {
        const scheduler::detail::schedule_unwrapper<D> holder;
        s1.accept(holder);
        concat(s0, holder.get());
        return;
    }
}