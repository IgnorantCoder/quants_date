#pragma once

namespace qd { namespace unary {
    template <typename E>
    class unary_expression {
    public:
        using expression_type = E;

    public:
        virtual ~unary_expression() = default;

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
        static_cast<expression_type&>(*this).do_apply(y, m, d);
        return;
    }

    template<typename E>
    inline void unary_expression<E>::apply(
        const std::size_t y,
        const std::size_t m,
        const std::size_t d) const
    {
        static_cast<const expression_type&>(*this).do_apply(y, m, d);
        return;
    }
}}
