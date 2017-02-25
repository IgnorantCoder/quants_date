#pragma once

#include "quants_date/date.h"
#include "quants_date/binary/binary_expression.h"

namespace qd {
    template <typename D>
    class date_range {
    public:
        using inner_date_type = D;

    private:
        static_assert(
            type_traits::is_date_compatible<inner_date_type>::value,
            "D is not compatible to this adaptor.");

    public:
        date_range(
            const inner_date_type& from,
            const inner_date_type& to);
        date_range(
            inner_date_type&& from,
            inner_date_type&& to);

    public:
        template <typename E>
        void accept(binary::binary_expression<E>& binary) const;

        template <typename E>
        void accept(const binary::binary_expression<E>& binary) const;

    private:
        inner_date_type _from;
        inner_date_type _to;
    };

    template<typename D>
    inline date_range<D>::date_range(
        const inner_date_type & from, 
        const inner_date_type & to)
        : _from(from),
        _to(to)
    {
    }

    template<typename D>
    inline date_range<D>::date_range(
        inner_date_type&& from,
        inner_date_type&& to)
        : _from(std::move(from)),
        _to(std::move(to))
    {
    }

    template<typename D>
    template<typename E>
    inline void date_range<D>::accept(binary::binary_expression<E>& binary) const
    {
        binary.apply(
            _from.year(),
            _from.month(),
            _from.day(),
            _to.year(),
            _to.month(),
            _to.day());
        return;
    }

    template<typename D>
    template<typename E>
    inline void date_range<D>::accept(const binary::binary_expression<E>& binary) const
    {
        binary.apply(
            _from.year(),
            _from.month(),
            _from.day(),
            _to.year(),
            _to.month(),
            _to.day());
        return;
    }

}