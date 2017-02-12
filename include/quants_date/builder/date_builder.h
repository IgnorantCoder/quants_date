#pragma once

#include "quants_date/date.h"

#include "quants_date/unary/to_serial_value.h"

namespace qd { namespace builder {
    template <typename D>
    struct create_from_ymd_traits;

    template <typename D>
    struct create_null_object_traits;
}}

namespace qd {
    template <typename D>
    typename builder::create_null_object_traits<D>::result_type
    create_date()
    {
        return builder::create_null_object_traits<D>::apply();
    }
    
    template <typename D>
    typename builder::create_from_ymd_traits<D>::result_type
    create_date(
        const std::size_t y,
        const std::size_t m,
        const std::size_t d)
    {
        return builder::create_from_ymd_traits<D>::apply(y, m, d);
    }

    template <typename D>
    auto create_date(const std::size_t serial_value)
        -> decltype(create_date<D>(1900, 1, 1))
    {
        using data = qd::unary::detail::the_number_of_accumulate_days_data;
        const auto ym = data::find(serial_value);
        const auto y = ym.first;
        const auto m = ym.second;
        const auto d = serial_value - data::value(y, m);

        return create_date<D>(y, m, d);
    }
}