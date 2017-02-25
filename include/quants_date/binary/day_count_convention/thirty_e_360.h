#pragma once

#include <algorithm>
#include <cstddef>

#include "quants_date/binary/day_count_convention/day_count_convention_expression.h"

namespace qd { namespace binary { namespace dcc {
    class thirty_e_360 : public day_count_convention_expression<thirty_e_360> {
    public:
        thirty_e_360();
        thirty_e_360(const thirty_e_360& other);

    public:
        double calculate_day_count(
            const std::size_t from_y,
            const std::size_t from_m,
            const std::size_t from_d,
            const std::size_t to_y,
            const std::size_t to_m,
            const std::size_t to_d) const;
    };

    inline thirty_e_360::thirty_e_360()
    {
    }

    inline thirty_e_360::thirty_e_360(const thirty_e_360 & other)
    {
    }

    inline double thirty_e_360::calculate_day_count(
        const std::size_t from_y, 
        const std::size_t from_m,
        const std::size_t from_d,
        const std::size_t to_y,
        const std::size_t to_m,
        const std::size_t to_d) const
    {
        const int y = static_cast<int>(from_y) - static_cast<int>(to_y);
        const int m = static_cast<int>(from_m) - static_cast<int>(to_m);

        const int adjusted_from_d 
            = std::min(static_cast<int>(from_d), 30);
        const int adjusted_to_d
            = std::min(static_cast<int>(to_d), 30);
        const int d = adjusted_from_d - adjusted_to_d;

        return y + m / 12. + d / 360.;
    }
}}}