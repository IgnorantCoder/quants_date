#pragma once

#include "quants_date/date_range.h"
#include "quants_date/binary/binary_expression.h"
#include "quants_date/binary/day_count_convention/day_count_convention_expression.h"

namespace qd { namespace binary {
    template <typename C>
    class day_count_fraction : public binary_expression<day_count_fraction<C>> {
    private:
        using convention_type = C;
        using base_type = binary_expression<day_count_fraction<C>>;
        friend class base_type;

    public:
        day_count_fraction(const convention_type& convention);

    public:
        using result_type = double;

    public:
        result_type get() const;

    private:
        void do_apply(
            const std::size_t from_y,
            const std::size_t from_m,
            const std::size_t from_d,
            const std::size_t to_y,
            const std::size_t to_m,
            const std::size_t to_d) const;

    private:
        mutable result_type _result;
        convention_type _convention;
    };

    template<typename C>
    inline day_count_fraction<C>::day_count_fraction(
        const convention_type& convention)
        : _result(),
        _convention(convention)
    {
    }

    template<typename C>
    inline typename day_count_fraction<C>::result_type 
    day_count_fraction<C>::get() const
    {
        return _result;
    }

    template<typename C>
    inline void day_count_fraction<C>::do_apply(
        const std::size_t from_y, 
        const std::size_t from_m, 
        const std::size_t from_d, 
        const std::size_t to_y, 
        const std::size_t to_m,
        const std::size_t to_d) const
    {
        this->_result = _convention.calculate_day_count(
            from_y, from_m, from_d,
            to_y, to_m, to_d);
    }
} }

namespace qd {
    template<typename D, typename C>
    typename binary::day_count_fraction<C>::result_type
    day_count_fraction(
        const date_range<D>& d,
        const binary::dcc::day_count_convention_expression<C>& convention)
    {
        const binary::day_count_fraction<C> calculator(convention());
        d.accept(calculator);
        return calculator.get();
    }
}