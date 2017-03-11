#pragma once

#include <cstddef>

#include "quants_date/binary/fwd.h"
#include "quants_date/binary/day_count_convention/day_count_convention_expression.h"

namespace qd { namespace binary { namespace dcc {
    class one_one : public day_count_convention_expression<one_one> {
        friend class day_count_fraction<one_one>;

    public:
        one_one();
        one_one(const one_one& other);

    private:
        double calculate_day_count(
            const std::size_t from_y,
            const std::size_t from_m,
            const std::size_t from_d,
            const std::size_t to_y,
            const std::size_t to_m,
            const std::size_t to_d) const;
    };

    inline one_one::one_one()
    {
    }

    inline one_one::one_one(const one_one& other)
    {
    }

    inline double one_one::calculate_day_count(
        const std::size_t from_y, 
        const std::size_t from_m, 
        const std::size_t from_d, 
        const std::size_t to_y, 
        const std::size_t to_m, 
        const std::size_t to_d) const
    {
        return 1.0;
    }
}}}