#pragma once

#include <cstddef>

#include "quants_date/binary/fwd.h"
#include "quants_date/binary/day_count_convention/day_count_convention_expression.h"

namespace qd { namespace binary { namespace dcc {
    class constant_value 
        : public day_count_convention_expression<constant_value> {
        friend class day_count_fraction<constant_value>;

    public:
        constant_value(const double value);
        constant_value(const constant_value& other);

    private:
        double calculate_day_count(
            const std::size_t /*from_y*/,
            const std::size_t /*from_m*/,
            const std::size_t /*from_d*/,
            const std::size_t /*to_y*/,
            const std::size_t /*to_m*/,
            const std::size_t /*to_d*/) const;

    private:
        double _value;
    };

    inline constant_value::constant_value(const double value)
        :_value(value)
    {
    }

    inline constant_value::constant_value(const constant_value& other)
        : _value(other._value)
    {
    }

    inline double constant_value::calculate_day_count(
        const std::size_t /*from_y*/, 
        const std::size_t /*from_m*/, 
        const std::size_t /*from_d*/, 
        const std::size_t /*to_y*/, 
        const std::size_t /*to_m*/, 
        const std::size_t /*to_d*/) const
    {
        return this->_value;
    }
}}}