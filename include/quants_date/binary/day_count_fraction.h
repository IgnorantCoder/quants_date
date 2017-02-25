#pragma once

#include <algorithm>
#include <string>
#include <limits>

#include "quants_date/date_range.h"
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

    template<typename D>
    double day_count_fraction(
        const date_range<D>& d,
        const std::string& convention)
    {
        std::string lower_convention(convention.size());
        std::transform(
            convention.cbegin(),
            convention.cend(),
            lower_convention.begin(),
            ::tolower);

        switch (lower_convention) {
        case "actual/360":
        case "act/360":
        case "a/360":
        case "french":
            return day_count_fraction(d, binary::dcc::actual_360);
        case "act/365fixed":
        case "a/365fixed":
        case "a/365f":
        case "english":
            return day_count_fraction(d, binary::dcc::actual_365_fixed);
        case "actual/actual":
        case "actual/actualisda":
        case "act/act":
        case "actual/365":
        case "act/365":
            return day_count_fraction(d, binary::dcc::actual_actual);
        case "one/one":
        case "1/1":
            return day_count_fraction(d, binary::dcc::one_one);
        case "30/360bondbasis":
        case "30a/360":
            return day_count_fraction(d, binary::dcc::thirty_360_bond_basis);
        case "30e/360":
        case "30/360icma":
        case "30s/360":
        case "eurobondbasis":
        case "specialgerman":
            return day_count_fraction(d, binary::dcc::thirty_e_360);
        }

        return std::numeric_limits<
            typename binary::day_count_fraction<C>::result_type
        >::quiet_NaN();
    }
}