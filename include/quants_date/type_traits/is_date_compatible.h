#pragma once

#include <type_traits>

namespace qd { namespace type_traits { 
    namespace detail {
        template <typename T>
        struct has_year_accessor {
        private:
            template <typename U>
            static auto check(U u) -> decltype(u.year(), std::true_type());
            static auto check(...) -> decltype(std::false_type());

        public:
            using type = decltype(check(std::declval<T>()));
            static constexpr bool value = type::value;
        };

        template <typename T>
        struct has_month_accessor {
        private:
            template <typename U>
            static auto check(U u) -> decltype(u.month(), std::true_type());
            static auto check(...) -> decltype(std::false_type());

        public:
            using type = decltype(check(std::declval<T>()));
            static constexpr bool value = type::value;
        };

        template <typename T>
        struct has_day_accessor {
        private:
            template <typename U>
            static auto check(U u) -> decltype(u.day(), std::true_type());
            static auto check(...) -> decltype(std::false_type());

        public:
            using type = decltype(check(std::declval<T>()));
            static constexpr bool value = type::value;
        };

        template <typename T>
        class has_less_than_operator {
        private:
            template <typename U>
            static auto check(U u, U other) -> decltype(u < other, std::true_type());
            static auto check(...) -> decltype(std::false_type());

        public:
            using type = decltype(check(std::declval<T>(), std::declval<T>()));
            static constexpr bool value = type::value;
        };
    }

    template <typename T>
    struct is_date_compatible {
    private:
        static constexpr bool has_year
            = typename detail::has_year_accessor<T>::value;
        static constexpr bool has_month
            = typename detail::has_month_accessor<T>::value;
        static constexpr bool has_day
            = typename detail::has_day_accessor<T>::value;
        static constexpr bool less_than_compareble
            = typename detail::has_less_than_operator<T>::value;

    private:
        static_assert(
            has_year,
            "Please implement year() to T");
        static_assert(
            has_month,
            "Please implement month() to T");
        static_assert(
            has_day,
            "Please implement day() to T");
        static_assert(
            less_than_compareble,
            "Please implement operator< to T");

    public:
        static constexpr bool value
            = has_year
            && has_month
            && has_day
            && less_than_compareble;
        using type = std::integral_constant<bool, value>;
    };
}}