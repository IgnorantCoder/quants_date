#pragma once

#include <algorithm>
#include <set>

#include "quants_date/builder/date_builder.h"
#include "quants_date/detail/schedule_type.h"
#include "quants_date/schedule.h"
#include "quants_date/scheduler/modifier_expression.h"
#include "quants_date/unary/to_serial_value.h"
#include "quants_date/unary/unary_expression.h"

namespace qd { namespace scheduler {
    namespace detail {
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
    }

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