#pragma once

#include <algorithm>
#include <cstddef>

#include "quants_date/binary/fwd.h"
#include "quants_date/binary/day_count_convention/day_count_convention_expression.h"

namespace qd { namespace binary { namespace dcc {
    class thirty_360_bond_basis 
        : public day_count_convention_expression<thirty_360_bond_basis> {
        friend class day_count_fraction<thirty_360_bond_basis>;

    public:
        thirty_360_bond_basis();
        thirty_360_bond_basis(const thirty_360_bond_basis& other);

    private:
        double calculate_day_count(
            const std::size_t from_y,
            const std::size_t from_m,
            const std::size_t from_d,
            const std::size_t to_y,
            const std::size_t to_m,
            const std::size_t to_d) const;
    };

    inline thirty_360_bond_basis::thirty_360_bond_basis()
    {
    }

    inline thirty_360_bond_basis::thirty_360_bond_basis(const thirty_360_bond_basis & other)
    {
    }

    inline double thirty_360_bond_basis::calculate_day_count(
        const std::size_t from_y, 
        const std::size_t from_m,
        const std::size_t from_d,
        const std::size_t to_y,
        const std::size_t to_m,
        const std::size_t to_d) const
    {
        const int y = static_cast<int>(to_y) - static_cast<int>(from_y);
        const int m = static_cast<int>(to_m) - static_cast<int>(from_m);

        const int adjusted_from_d 
            = std::min(static_cast<int>(from_d), 30);
        const int adjusted_to_d
            = adjusted_from_d == 30
            ? std::min(static_cast<int>(to_d), 30)
            : static_cast<int>(to_d);
        const int d = adjusted_to_d - adjusted_from_d;

        return y + m / 12. + d / 360.;
    }
}}}