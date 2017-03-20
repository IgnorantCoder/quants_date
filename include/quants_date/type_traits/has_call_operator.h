#pragma once

#include <type_traits>
#include <utility>
#include "quants_date/type_traits/is_detected.h"

namespace qd { namespace type_traits {
    template <typename T, typename... Args>
    using call_operator_type 
        = decltype(std::declval<T>()(std::declval<Args>()...));

    template <typename T, typename... Args>
    using has_call_operator = is_detected<call_operator_type, T, Args... >;

    template <typename T, typename A>
    class has_unary_operator : public has_call_operator<T, A> {};

    template <typename T, typename A0, typename A1>
    class has_binary_operator : public has_call_operator<T, A0, A1> {};
} }