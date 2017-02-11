#pragma once

#include <type_traits>

#include "quants_date/type_traits/is_date_compatible.h"

namespace qd { namespace unary {
    template <typename E>
    class unary_expression {
    public:
        using expression_type = E;

    public:
        void apply(
            const std::size_t y,
            const std::size_t m,
            const std::size_t d);

        void apply(
            const std::size_t y,
            const std::size_t m, 
            const std::size_t d) const;
    };

    template<typename E>
    inline void unary_expression<E>::apply(
        const std::size_t y, 
        const std::size_t m, 
        const std::size_t d)
    {
        static_cast<expression_type&>(*this).doApply(y, m, d);
        return;
    }

    template<typename E>
    inline void unary_expression<E>::apply(
        const std::size_t y,
        const std::size_t m,
        const std::size_t d) const
    {
        static_cast<const expression_type&>(*this).doApply(y, m, d);
        return;
    }
}}
