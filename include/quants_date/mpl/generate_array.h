#pragma once

#include <cstddef>
#include <utility>

namespace qd { namespace mpl {
    namespace detail {
        template<typename T, T... args> 
        struct array_holder /*: public std::integer_sequence<T, args...>*/ {
            static constexpr std::size_t size = sizeof... (args);
            static constexpr T data[size] = { args... };
        };

        template<size_t N, template<size_t> typename F, typename T, T... args>
        struct generate_array_impl {
            using result = typename generate_array_impl<
                N - 1,
                F,
                T,
                F<N>::value, args...
            >::result;
        };

        template<template<std::size_t> class F, typename T, T... args>
        struct generate_array_impl<0, F, T, args...> {
            using result = array_holder<T, F<0>::value, args...>;
        };
    }

    template<typename R, size_t N, template<std::size_t> class F>
    struct generate_array {
    public:
        using value_type = R;
        using result = typename detail::generate_array_impl<
            N - 1,
            F,
            value_type
        >::result;
    };
}}