#pragma once

#include "quants_date/detail/schedule_type.h"

namespace qd { namespace scheduler {
    template <typename E>
    class selector_expression {
    public:
        using expression_type = E;

        template <typename D>
        using schedule_type = qd::detail::schedule_type<D>;

    public:
        virtual ~selector_expression() = default;

    public:
        template <typename D>
        void apply(const typename schedule_type<D>::container_type& data);
        template <typename D>
        void apply(const typename schedule_type<D>::container_type& data) const;
    };

    template<typename E>
    template<typename D>
    inline void qd::scheduler::selector_expression<E>::apply(
        const typename schedule_type<D>::container_type& data)
    {
        static_cast<expression_type&>(*this).do_apply(data);
        return;
    }

    template<typename E>
    template<typename D>
    inline void qd::scheduler::selector_expression<E>::apply(
        const typename schedule_type<D>::container_type& data) const
    {
        static_cast<const expression_type&>(*this).do_apply(data);
        return;
    }
}}