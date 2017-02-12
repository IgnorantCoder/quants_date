#pragma once

#include <type_traits>

namespace qd { namespace mpl {
    template <std::size_t M, std::size_t X>
    struct is_multiple_of
        : public std::integral_constant<bool, X % M == 0>
    {};
}}