#pragma once

#include "quants_date/type_traits/is_date_compatible.h"

namespace qd { namespace mix_in {
    template <typename T>
    class implement_comparable {
    public:
        friend bool operator> (const T& lhs, const T& rhs) { return rhs < lhs; }
        friend bool operator<=(const T& lhs, const T& rhs) { return !(rhs < lhs); }
        friend bool operator>=(const T& lhs, const T& rhs) { return !(lhs < rhs); }
        friend bool operator==(const T& lhs, const T& rhs) { return !(lhs != rhs); }
        friend bool operator!=(const T& lhs, const T& rhs) { return lhs < rhs || rhs < lhs; }
    };
}}