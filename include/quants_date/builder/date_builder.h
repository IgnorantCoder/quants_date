#pragma once

#include <tuple>

#include "quants_date/date.h"
#include "quants_date/unary/to_serial_value.h"

namespace qd { namespace builder {
    template <typename D>
    struct create_from_ymd_traits {
        using result_type = D;
        static result_type apply(
            const std::size_t y,
            const std::size_t m,
            const std::size_t d)
        {
            return result_type(y, m, d);
        }
    };

    template <typename D>
    struct create_null_object_traits {
        using result_type = D;
        static result_type apply()
        {
            return result_type();
        }
    };
}}

namespace qd {
    template <typename D>
    date<D> create_date()
    {
        return builder::create_null_object_traits<D>::apply();
    }
    
    template <typename D>
    date<D> create_date(
        const std::size_t y,
        const std::size_t m,
        const std::size_t d)
    {
        auto&& data = builder::create_from_ymd_traits<D>::apply(y, m, d);
        return date<D>(std::move(data));
    }

    template <typename D>
    auto create_date(
        const std::tuple<std::size_t, std::size_t, std::size_t>& data)
        -> decltype(create_date<D>(1900, 1, 1))
    {
        enum {
            Year = 0,
            Month,
            Day
        };

        return create_date<D>(
            std::get<Year>(data),
            std::get<Month>(data),
            std::get<Day>(data));
    }

    template <typename D>
    auto create_date(const std::size_t serial_value)
        -> decltype(create_date<D>(1900, 1, 1))
    {
        using data = qd::unary::detail::the_sum_of_days_data;
        const auto ym = data::find(serial_value);
        const auto y = ym.first;
        const auto m = ym.second;
        const auto d = serial_value - data::value(y, m);

        return create_date<D>(y, m, d);
    }
}