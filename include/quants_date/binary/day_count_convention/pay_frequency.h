#pragma once

#include <type_traits>

namespace qd { namespace binary { namespace dcc {
    class annual : public std::integral_constant<std::size_t, 1> {
    public:
        static constexpr double coupon_factor = 1.0 / value;
    };

    class semi_annual : public std::integral_constant<std::size_t, 2> {
    public:
        static constexpr double coupon_factor = 1.0 / value;
    };

    class quarterly : public std::integral_constant<std::size_t, 4> {
    public:
        static constexpr double coupon_factor = 1.0 / value;
    };

    class monthly : public std::integral_constant<std::size_t, 12> {
    public:
        static constexpr double coupon_factor = 1.0 / value;
    };

    template <typename T>
    struct is_pay_frequency : public std::false_type {};

    template <>
    struct is_pay_frequency<annual> : public std::true_type {};

    template <>
    struct is_pay_frequency<semi_annual> : public std::true_type {};

    template <>
    struct is_pay_frequency<quarterly> : public std::true_type {};

    template <>
    struct is_pay_frequency<monthly> : public std::true_type {};
}}}