#pragma once

#include <type_traits>
#include <utility>

namespace qd { namespace type_traits {
    namespace detail {
        template <
            class Default, 
            class AlwaysVoid,
            template<class...> class Op,
            class... Args>
        struct detector {
            using value_t = std::false_type;
            using type = Default;
        };

        template <
            class Default, 
            template<class...> class Op,
            class... Args>
        struct detector<Default, std::void_t<Op<Args...>>, Op, Args...> {
            using value_t = std::true_type;
            using type = Op<Args...>;
        };
    }

    struct nonesuch {
        nonesuch() = delete;
        ~nonesuch() = delete;
        nonesuch(nonesuch const&) = delete;
        void operator=(nonesuch const&) = delete;
    };

    template <template<class...> class Op, class... Args>
    using is_detected = typename detail::detector<nonesuch, void, Op, Args...>::value_t;
}}