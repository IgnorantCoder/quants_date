#pragma once

#include "quants_date/date.h"
#include "quants_date/binary/count_days.h"
#include "quants_date/binary/day_count_fraction.h"
#include "quants_date/builder/date_range_builder.h"

namespace qd {
    template<typename D>
    binary::days_counter::result_type
    count_days(const date<D>& d0, const date<D>& d1)
    {
        const auto d = create_date_range(d0, d1);
        return count_days(d);
    }

    template<typename D>
    typename binary::day_count_fraction<binary::dcc::actual_360>::result_type
    year_fraction_actual_360(const date<D>& d0, const date<D>& d1)
    {
        const auto d = create_date_range(d0, d1);
        return year_fraction_actual_360(d);
    }

    template<typename D>
    typename binary::day_count_fraction<binary::dcc::actual_365_fixed>::result_type
    year_fraction_actual_365_fixed(const date<D>& d0, const date<D>& d1)
    {
        const auto d = create_date_range(d0, d1);
        return year_fraction_actual_365_fixed(d);
    }

    template<typename D>
    typename binary::day_count_fraction<binary::dcc::actual_actual>::result_type
    year_fraction_actual_actual(const date<D>& d0, const date<D>& d1)
    {
        const auto d = create_date_range(d0, d1);
        return year_fraction_actual_actual(d);
    }

    template<typename D>
    typename binary::day_count_fraction<binary::dcc::constant_value>::result_type
    year_fraction_one_one(const date<D>& d0, const date<D>& d1)
    {
        const auto d = create_date_range(d0, d1);
        return year_fraction_one_one(d);
    }

    template<typename D>
    typename binary::day_count_fraction<binary::dcc::thirty_360_bond_basis>::result_type
    year_fraction_30_360_bond_basis(const date<D>& d0, const date<D>& d1)
    {
        const auto d = create_date_range(d0, d1);
        return year_fraction_30_360_bond_basis(d);
    }

    template<typename D>
    typename binary::day_count_fraction<binary::dcc::thirty_e_360>::result_type
    year_fraction_30e_360(const date<D>& d0, const date<D>& d1)
    {
        const auto d = create_date_range(d0, d1);
        return year_fraction_30e_360(d);
    }

    template<typename D>
    typename binary::day_count_fraction<binary::dcc::thirty_e_360_isda>::result_type
    year_fraction_30e_360_isda(
        const date<D>& d0,
        const date<D>& d1,
        const date<D>& maturity_date)
    {
        const auto d = create_date_range(d0, d1);
        return year_fraction_30e_360_isda(d, maturity_date);
    }

    template<typename F, typename D>
    typename binary::day_count_fraction<
        binary::dcc::actual_365l<F>
    >::result_type
    year_fraction_actual_365l(
        const date<D>& d0,
        const date<D>& d1)
    {
        const auto d = create_date_range(d0, d1);
        return year_fraction_actual_365l(d);
    }

    template<typename D>
    typename binary::day_count_fraction<
        binary::dcc::actual_365l<binary::dcc::annual>
    >::result_type
    year_fraction_actual_365l(
        const date<D>& d0,
        const date<D>& d1,
        const std::string& frequency)
    {
        const auto d = create_date_range(d0, d1);
        return year_fraction_actual_365l(d, frequency);
    }

    template<typename D>
    typename binary::day_count_fraction<
        binary::dcc::actual_365l<binary::dcc::annual>
    >::result_type
    year_fraction_actual_actual_icma(
        const date<D>& d0,
        const date<D>& d1,
        const date<D>& payment_date,
        const std::string& frequency)
    {
        const auto d = create_date_range(d0, d1);
        return year_fraction_actual_actual_icma(d, payment_date, frequency);
    }
}