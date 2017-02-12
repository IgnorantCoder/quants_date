#pragma once

#include <type_traits>

#include "quants_date/mpl/generate_array.h"
#include "quants_date/mpl/is_leap_year.h"

namespace qd { namespace mpl {
    namespace detail {
        template <std::size_t M>
        struct the_number_of_days_of_non_leap_year;

        template <>
        struct the_number_of_days_of_non_leap_year<1> 
            : public std::integral_constant<std::size_t, 31>
        {
        };

        template <>
        struct the_number_of_days_of_non_leap_year<2>
            : public std::integral_constant<std::size_t, 28>
        {
        };

        template <>
        struct the_number_of_days_of_non_leap_year<3>
            : public std::integral_constant<std::size_t, 31>
        {
        };

        template <>
        struct the_number_of_days_of_non_leap_year<4>
            : public std::integral_constant<std::size_t, 30>
        {
        };

        template <>
        struct the_number_of_days_of_non_leap_year<5>
            : public std::integral_constant<std::size_t, 31>
        {
        };

        template <>
        struct the_number_of_days_of_non_leap_year<6>
            : public std::integral_constant<std::size_t, 30>
        {
        };

        template <>
        struct the_number_of_days_of_non_leap_year<7>
            : public std::integral_constant<std::size_t, 31>
        {
        };

        template <>
        struct the_number_of_days_of_non_leap_year<8>
            : public std::integral_constant<std::size_t, 31>
        {
        };

        template <>
        struct the_number_of_days_of_non_leap_year<9>
            : public std::integral_constant<std::size_t, 30>
        {
        };

        template <>
        struct the_number_of_days_of_non_leap_year<10>
            : public std::integral_constant<std::size_t, 31>
        {
        };

        template <>
        struct the_number_of_days_of_non_leap_year<11>
            : public std::integral_constant<std::size_t, 30>
        {
        };

        template <>
        struct the_number_of_days_of_non_leap_year<12>
            : public std::integral_constant<std::size_t, 31>
        {
        };

        template <std::size_t M>
        struct the_number_of_days_of_leap_year
            : public the_number_of_days_of_non_leap_year<M>
        {
        };

        template <>
        struct the_number_of_days_of_leap_year<2>
            : public std::integral_constant<std::size_t, 29>
        {
        };

        template <std::size_t Y, std::size_t M>
        struct the_number_of_days_calculator
            : public std::conditional<
                is_leap_year<Y>::value,
                the_number_of_days_of_leap_year<M>,
                the_number_of_days_of_non_leap_year<M>
            >::type
        {};

        template <std::size_t Y>
        struct the_number_of_accumulate_days_based_on_year_calculator
            : public std::integral_constant<
                std::size_t,
                the_number_of_accumulate_days_based_on_year_calculator<Y - 1>::value
                + (is_leap_year<Y>::value ? 366 : 365)>
        {};

        template <>
        struct the_number_of_accumulate_days_based_on_year_calculator<1899>
            : public std::integral_constant<std::size_t, 0>
        {};

        template <std::size_t Y, std::size_t M>
        struct the_number_of_days_from_this_year_calculator
            : public std::integral_constant<
                std::size_t,
                the_number_of_days_calculator<Y, M>::value
                + the_number_of_days_from_this_year_calculator<Y, M - 1>::value>
        {};


        template <std::size_t Y>
        struct the_number_of_days_from_this_year_calculator<Y, 0>
            : public std::integral_constant<std::size_t, 0>
        {};

        template <std::size_t Y, std::size_t M>
        struct the_number_of_accumulate_days_calculator
            : public std::integral_constant<
                std::size_t,
                the_number_of_accumulate_days_based_on_year_calculator<Y - 1>::value
                + the_number_of_days_from_this_year_calculator<Y, M - 1>::value
            >
        {};
    }

    template <std::size_t Y>
    struct the_number_of_days_data {
    private:
        template <std::size_t M>
        using meta_func = detail::the_number_of_days_calculator<Y, M + 1>;
        using result = typename generate_array<
            typename meta_func<0>::value_type,
            12,
            meta_func
        >::result;

    public:
        static constexpr auto data = result::data;
        using value_type = decltype(data);
    };

    template <std::size_t Y>
    struct the_number_of_accumulate_days_data {
    private:
        template <std::size_t M>
        using meta_func = detail::the_number_of_accumulate_days_calculator<Y, M + 1>;
        using result = typename generate_array<
            typename meta_func<0>::value_type,
            12,
            meta_func
        >::result;

    public:
        static constexpr auto data = result::data;
        using value_type = decltype(data);
    };
} }