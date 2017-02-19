#pragma once

namespace qd { namespace binary {
    template <typename E>
    class binary_expression {
    public:
        using expression_type = E;

    public:
        void apply(
            const std::size_t from_y,
            const std::size_t from_m,
            const std::size_t from_d,
            const std::size_t to_y,
            const std::size_t to_m,
            const std::size_t to_d);

        void apply(
            const std::size_t from_y,
            const std::size_t from_m,
            const std::size_t from_d,
            const std::size_t to_y,
            const std::size_t to_m,
            const std::size_t to_d) const;
    };

    template<typename E>
    inline void binary_expression<E>::apply(
        const std::size_t from_y,
        const std::size_t from_m,
        const std::size_t from_d,
        const std::size_t to_y,
        const std::size_t to_m,
        const std::size_t to_d)
    {
        static_cast<expression_type&>(*this).do_apply(
            from_y,
            from_m,
            from_d,
            to_y,
            to_m,
            to_d);
        return;
    }

    template<typename E>
    inline void binary_expression<E>::apply(
        const std::size_t from_y,
        const std::size_t from_m,
        const std::size_t from_d,
        const std::size_t to_y,
        const std::size_t to_m,
        const std::size_t to_d) const
    {
        static_cast<const expression_type&>(*this).do_apply(
            from_y,
            from_m,
            from_d, 
            to_y,
            to_m, 
            to_d);
        return;
    }
}}

