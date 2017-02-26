#pragma once

#include <algorithm>
#include <string>
#include <limits>
#include <type_traits>
#include <functional>

#include "quants_date/date.h"
#include "quants_date/date_range.h"
#include "quants_date/string_algorithm/to_lower.h"
#include "quants_date/binary/binary_expression.h"
#include "quants_date/binary/day_count_convention/day_count_convention_expression.h"
#include "quants_date/binary/day_count_convention/actual_360.h"
#include "quants_date/binary/day_count_convention/actual_365_fixed.h"
#include "quants_date/binary/day_count_convention/actual_365l.h"
#include "quants_date/binary/day_count_convention/actual_actual.h"
#include "quants_date/binary/day_count_convention/actual_actual_icma.h"
#include "quants_date/binary/day_count_convention/one_one.h"
#include "quants_date/binary/day_count_convention/thirty_360_bond_basis.h"
#include "quants_date/binary/day_count_convention/thirty_e_360.h"
#include "quants_date/binary/day_count_convention/thirty_e_360_isda.h"
#include "quants_date/binary/day_count_convention/pay_frequency.h"

namespace qd { namespace binary {
    template <typename C>
    class day_count_fraction 
        : public binary_expression<day_count_fraction<C>> {
    private:
        using convention_type = C;
        using base_type = binary_expression<day_count_fraction<C>>;
        friend class base_type;

    public:
        day_count_fraction(const convention_type& convention);
        day_count_fraction(convention_type&& convention);

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
    inline day_count_fraction<C>::day_count_fraction(
        convention_type && convention)
        : _result(),
        _convention(std::move(convention))
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

    template<typename D, typename C>
    typename binary::day_count_fraction<C>::result_type
    day_count_fraction(
        const date_range<D>& d,
        binary::dcc::day_count_convention_expression<C>&& convention)
    {
        const binary::day_count_fraction<C> calculator(std::move(convention()));
        d.accept(calculator);
        return calculator.get();
    }

    template<typename D>
    typename binary::day_count_fraction<binary::dcc::actual_360>::result_type
    year_fraction_actual_360(const date_range<D>& range)
    {
        return qd::day_count_fraction(
            range,
            binary::dcc::actual_360());
    }

    template<typename D>
    typename binary::day_count_fraction<binary::dcc::actual_365_fixed>::result_type
    year_fraction_actual_365_fixed(const date_range<D>& range)
    {
        return qd::day_count_fraction(
            range,
            binary::dcc::actual_365_fixed());
    }

    template<typename D>
    typename binary::day_count_fraction<binary::dcc::actual_actual>::result_type
    year_fraction_actual_actual(const date_range<D>& range)
    {
        return qd::day_count_fraction(
            range,
            binary::dcc::actual_actual());
    }

    template<typename D>
    typename binary::day_count_fraction<binary::dcc::one_one>::result_type
    year_fraction_one_one(const date_range<D>& range)
    {
        return qd::day_count_fraction(
            range,
            binary::dcc::one_one());
    }

    template<typename D>
    typename binary::day_count_fraction<binary::dcc::thirty_360_bond_basis>::result_type
    year_fraction_30_360_bond_basis(const date_range<D>& range)
    {
        return qd::day_count_fraction(
            range,
            binary::dcc::thirty_360_bond_basis());
    }

    template<typename D>
    typename binary::day_count_fraction<binary::dcc::thirty_e_360>::result_type
    year_fraction_30e_360(const date_range<D>& range)
    {
        return qd::day_count_fraction(
            range,
            binary::dcc::thirty_e_360());
    }

    template<typename D>
    typename binary::day_count_fraction<binary::dcc::thirty_e_360_isda>::result_type
    year_fraction_30e_360_isda(
        const date_range<D>& range,
        const date<D>& maturity_date)
    {
        return qd::day_count_fraction(
            range,
            binary::dcc::thirty_e_360_isda(maturity_date));
    }

    template<typename F, typename D>
    typename binary::day_count_fraction<
        binary::dcc::actual_365l<F>
    >::result_type
    year_fraction_actual_365l(
        const date_range<D>& range)
    {
        return qd::day_count_fraction(
            range,
            binary::dcc::actual_365l<F>());
    }

    template<typename D>
    typename binary::day_count_fraction<
        binary::dcc::actual_365l<binary::dcc::annual>
    >::result_type
    year_fraction_actual_365l(
        const date_range<D>& range,
        const std::string& frequency)
    {
        const auto builder = binary::dcc::actual_365l_builder();
        auto&& dcc = binary::dcc::create_type_erasure(builder, frequency);
        return qd::day_count_fraction(range, std::move(dcc));
    }

    template<typename D>
    typename binary::day_count_fraction<
        binary::dcc::actual_365l<binary::dcc::annual>
    >::result_type
    year_fraction_actual_actual_icma(
        const date_range<D>& range,
        const date<D>& payment_date,
        const std::string& frequency)
    {
        const auto builder
            = binary::dcc::actual_actual_icma_builder(payment_date);
        auto&& dcc = binary::dcc::create_type_erasure(builder, frequency);
        return qd::day_count_fraction(range, std::move(dcc));
    }
}