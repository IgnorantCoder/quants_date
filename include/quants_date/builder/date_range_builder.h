#pragma once

#include "quants_date/date_range.h"
#include "quants_date/builder/date_builder.h"
#include "quants_date/unary/to_serial_value.h"

namespace qd {
    template <typename D>
    date_range<D> create_date_range()
    {
        return builder::create_null_object_traits<D>::apply();
    }

    template <typename D>
    date_range<D> create_date_range(
        const std::size_t from_y,
        const std::size_t from_m,
        const std::size_t from_d,
        const std::size_t to_y,
        const std::size_t to_m,
        const std::size_t to_d)
    {
        auto&& from = builder::create_from_ymd_traits<D>::apply(
            from_y,
            from_m,
            from_d);
        auto&& to = builder::create_from_ymd_traits<D>::apply(
            to_y, 
            to_m, 
            to_d);
        return date_range<D>(
            std::move(from),
            std::move(to));
    }

    template <typename D>
    auto create_date_range(
        const std::tuple<std::size_t, std::size_t, std::size_t>& from_data,
        const std::tuple<std::size_t, std::size_t, std::size_t>& to_data)
        -> decltype(create_date_range<D>(1900, 1, 1, 1900, 1, 1))
    {
        enum {
            Year = 0,
            Month,
            Day
        };

        return create_date_range<D>(
            std::get<Year>(from_data),
            std::get<Month>(from_data),
            std::get<Day>(from_data),
            std::get<Year>(to_data),
            std::get<Month>(to_data),
            std::get<Day>(to_data));
    }

    template <typename D>
    auto create_date_range(
        const std::size_t from_serial_value,
        const std::size_t to_serial_value)
        -> decltype(create_date_range<D>(1900, 1, 1, 1900, 1, 1))
    {
        using data = qd::unary::detail::the_sum_of_days_data;

        const auto from_ym = data::find(from_serial_value);
        const auto from_y = from_ym.first;
        const auto from_m = from_ym.second;
        const auto from_d = from_serial_value - data::value(from_y, from_m);

        const auto to_ym = data::find(to_serial_value);
        const auto to_y = to_ym.first;
        const auto to_m = to_ym.second;
        const auto to_d = to_serial_value - data::value(to_y, to_m);

        return create_date_range<D>(
            from_y, from_m, from_d,
            to_y, to_m, to_d);
    }
}
