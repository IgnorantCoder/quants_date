#pragma once

#include <string>
#include <type_traits>
#include <limits>

#include "quants_date/string_algorithm/to_lower.h"
#include "quants_date/binary/day_count_convention/constant_value.h"
#include "quants_date/binary/day_count_convention/type_erasure.h"

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

    template<typename B>
    type_erased_wrapper create_type_erasure(
        const B& builder,
        const std::string& frequency)
    {
        const auto lower_case_frequency
            = string_alg::to_lower(frequency);
        if ("annual" == lower_case_frequency) {
            return builder.create<annual>();
        }
        if ("semi-annual" == lower_case_frequency) {
            return builder.create<semi_annual>();
        }
        if ("quarterly" == lower_case_frequency) {
            return builder.create<quarterly>();
        }
        if ("monthly" == lower_case_frequency) {
            builder.create<monthly>();
        }
        return type_erased_wrapper(
            constant_value(std::numeric_limits<double>::quiet_NaN()));
    }
}}}