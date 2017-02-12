#pragma once

#include "quants_date/type_traits/is_date_compatible.h"
#include "quants_date/mix_in/implement_comparable.h"
#include "quants_date/unary/unary_expression.h"

namespace qd {
    template <typename D>
    class date : private mix_in::implement_comparable<date<D>> {
    public:
        using inner_date_type = D;

    private:
        static_assert(
            type_traits::is_date_compatible<inner_date_type>::value,
            "D is not compatible to this adaptor.");

    public:
        date(inner_date_type&& data);
        date(const inner_date_type& data);

    public:
        template <typename E>
        void accept(unary::unary_expression<E>& unary) const;

        template <typename E>
        void accept(const unary::unary_expression<E>& unary) const;

    private:
        inner_date_type _data;
    };

    template<typename D>
    inline date<D>::date(inner_date_type&& data)
        : _data(std::move(data))
    {
    }

    template<typename D>
    inline date<D>::date(const inner_date_type& data)
        : _data(data)
    {
    }

    template<typename D>
    template<typename E>
    inline void date<D>::accept(unary::unary_expression<E>& unary) const {
        unary.apply(
            this->_data.year(),
            this->_data.month(),
            this->_data.day());
        return;
    }

    template<typename D>
    template<typename E>
    inline void date<D>::accept(const unary::unary_expression<E>& unary) const {
        unary.apply(
            this->_data.year(),
            this->_data.month(),
            this->_data.day());
        return;
    }
}