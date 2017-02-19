#pragma once

#include "quants_date/date.h"
#include "quants_date/binary/binary_expression.h"

namespace qd {
    template <typename D>
    class date_range {
    public:
        date_range(
            const date<D>& from,
            const date<D>& to);

    public:
        template <typename E>
        void accept(unary::binary_expression<E>& binary) const;

        template <typename E>
        void accept(const unary::binary_expression<E>& binary) const;

    private:
        date<D> _from;
        date<D> _to;
    };

    template<typename D>
    inline date_range<D>::date_range(
        const date<D>& from, 
        const date<D>& to)
        : _from(from),
        _to(to)
    {
    }

    template<typename D>
    template<typename E>
    inline void date_range<D>::accept(unary::binary_expression<E>& binary) const
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
    inline void date_range<D>::accept(const unary::binary_expression<E>& binary) const
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