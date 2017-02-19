#pragma once

namespace qd { namespace binary { namespace dcc {
    template <typename E>
    class day_count_convention_expression {
    public:
        using expression_type = E;

    public:
        const expression_type& operator()() const;
    };

    template<typename E>
    inline const typename day_count_convention_expression<E>::expression_type&
    day_count_convention_expression<E>::operator()() const
    {
        return static_cast<const expression_type&>(*this);
    }
}}}