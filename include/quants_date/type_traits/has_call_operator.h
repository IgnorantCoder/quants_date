#pragma once

#include <type_traits>
#include <utility>

namespace qd { namespace type_traits {
    template <typename T, typename... A>
    class has_call_operator {
    private:
        template <typename U, typename... P>
        static auto check(U u, P... p) -> decltype(u(p...), std::true_type());
        static auto check(...) -> decltype(std::false_type());

    public:
        using type
            = decltype(check(std::declval<T>(), std::declval<A>()...));
        static constexpr bool value = type::value;
    };

    template <typename T, typename A>
    class has_unary_operator : public has_call_operator<T, A> {};

    template <typename T, typename A0, typename A1>
    class has_binary_operator : public has_call_operator<T, A0, A1> {};
} }