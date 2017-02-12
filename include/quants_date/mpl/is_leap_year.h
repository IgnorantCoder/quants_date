#pragma once

#include <type_traits>

#include "quants_date/mpl/is_multiple_of.h"

namespace qd { namespace mpl {
    template <std::size_t YEAR>
    struct is_leap_year
        : public std::conditional<
            is_multiple_of<400, YEAR>::value,
            std::true_type,
            typename std::conditional<
                is_multiple_of<100, YEAR>::value,
                std::false_type,
                typename is_multiple_of<4, YEAR>::type
            >::type
        >::type
    {};
}}