#pragma once

#include <set>

namespace qd { namespace detail {
    template <typename D>
    struct schedule_type {
        using inner_date_type = D;
        using container_type = std::set<inner_date_type>;
    };
} }