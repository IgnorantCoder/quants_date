#pragma once

#include <type_traits>

#include "quants_date/mpl/generate_array.h"
#include "quants_date/mpl/is_leap_year.h"

namespace qd { namespace mpl {
    namespace detail {
        template <std::size_t M>
        struct the_number_of_days_in_month_of_non_leap_year;

        template <>
        struct the_number_of_days_in_month_of_non_leap_year<1> 
            : public std::integral_constant<std::size_t, 31>
        {
        };

        template <>
        struct the_number_of_days_in_month_of_non_leap_year<2>
            : public std::integral_constant<std::size_t, 28>
        {
        };

        template <>
        struct the_number_of_days_in_month_of_non_leap_year<3>
            : public std::integral_constant<std::size_t, 31>
        {
        };

        template <>
        struct the_number_of_days_in_month_of_non_leap_year<4>
            : public std::integral_constant<std::size_t, 30>
        {
        };

        template <>
        struct the_number_of_days_in_month_of_non_leap_year<5>
            : public std::integral_constant<std::size_t, 31>
        {
        };

        template <>
        struct the_number_of_days_in_month_of_non_leap_year<6>
            : public std::integral_constant<std::size_t, 30>
        {
        };

        template <>
        struct the_number_of_days_in_month_of_non_leap_year<7>
            : public std::integral_constant<std::size_t, 31>
        {
        };

        template <>
        struct the_number_of_days_in_month_of_non_leap_year<8>
            : public std::integral_constant<std::size_t, 31>
        {
        };

        template <>
        struct the_number_of_days_in_month_of_non_leap_year<9>
            : public std::integral_constant<std::size_t, 30>
        {
        };

        template <>
        struct the_number_of_days_in_month_of_non_leap_year<10>
            : public std::integral_constant<std::size_t, 31>
        {
        };

        template <>
        struct the_number_of_days_in_month_of_non_leap_year<11>
            : public std::integral_constant<std::size_t, 30>
        {
        };

        template <>
        struct the_number_of_days_in_month_of_non_leap_year<12>
            : public std::integral_constant<std::size_t, 31>
        {
        };

        template <std::size_t M>
        struct the_number_of_days_in_month_of_leap_year
            : public the_number_of_days_in_month_of_non_leap_year<M>
        {
        };

        template <>
        struct the_number_of_days_in_month_of_leap_year<2>
            : public std::integral_constant<std::size_t, 29>
        {
        };

        template <std::size_t Y, std::size_t M>
        struct the_number_of_days_in_month
            : public std::conditional<
                is_leap_year<Y>::value,
                the_number_of_days_in_month_of_leap_year<M>,
                the_number_of_days_in_month_of_non_leap_year<M>
            >::type
        {};

        template <std::size_t Y>
        struct the_number_of_days_in_year
            : public std::conditional<
                is_leap_year<Y>::value,
                std::integral_constant<std::size_t, 366>,
                std::integral_constant<std::size_t, 365>
            >::type
        {};

        template <std::size_t Y>
        struct the_sum_of_days_based_on_year
            : public std::integral_constant<
                std::size_t,
                the_sum_of_days_based_on_year<Y - 1>::value
                + the_number_of_days_in_year<Y>::value>
        {};

        //This stop condition occurs compile error.
        //template <>
        //struct the_sum_of_days_based_on_year<1900>
        //    : public the_number_of_days_in_year<1900>
        //{};

        template <>
        struct the_sum_of_days_based_on_year<1899>
            : public std::integral_constant<std::size_t, 0>
        {};

        template <std::size_t Y, std::size_t M>
        struct the_sum_of_days_based_on_month_in_the_year
            : public std::integral_constant<
                std::size_t,
                the_number_of_days_in_month<Y, M>::value
                + the_sum_of_days_based_on_month_in_the_year<Y, M - 1>::value>
        {};

        template <std::size_t Y>
        struct the_sum_of_days_based_on_month_in_the_year<Y, 0>
            : public std::integral_constant<std::size_t, 0>
        {};

        template <std::size_t Y, std::size_t M>
        struct the_sum_of_days_based_on_month
            : public std::integral_constant<
                std::size_t,
                the_sum_of_days_based_on_year<Y - 1>::value
                + the_sum_of_days_based_on_month_in_the_year<Y, M - 1>::value
            >
        {};
    }

    template <std::size_t Y>
    struct the_number_of_days_data {
    private:
        template <std::size_t M>
        using meta_func = detail::the_number_of_days_in_month<Y, M + 1>;
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
    struct the_sum_of_days_data {
    private:
        template <std::size_t M>
        using meta_func = detail::the_sum_of_days_based_on_month<Y, M + 1>;
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