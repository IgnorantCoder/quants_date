#pragma once

#include <algorithm>
#include <set>
#include <random>

#include "quants_date/schedule.h"
#include "quants_date/unary/to_serial_value.h"
#include "quants_date/builder/date_builder.h"

namespace qd {
    namespace detail {
        std::mt19937& genRandomDevice()
        {
            static std::mt19937 mt(1);
            return mt;
        }
        

        template <typename D>
        void generate_random(std::set<D>& data, const std::size_t size)
        {
            if (data.size() == size) {
                return;
            }

            std::uniform_int_distribution<> dist(
                to_serial_value(create_min<D>()),
                to_serial_value(create_max<D>()));
            const auto gen = [&dist]() -> D
            {
                const auto serial_value = dist(genRandomDevice());
                using data = qd::unary::detail::the_sum_of_days_data;
                const auto ym = data::find(serial_value);
                const auto y = ym.first;
                const auto m = ym.second;
                const auto d = serial_value - data::value(y, m);
                return qd::builder::create_from_ymd_traits<D>::apply(y, m, d);
            };

            std::set<D> extend;
            for (std::size_t i = 0; i < size; ++i) {
                extend.insert(gen());
            }
            data.insert(std::cbegin(extend), std::cend(extend));

            return generate_random(data, size);
        }
    }

    template <typename D>
    schedule<D> generate_random(const std::size_t size)
    {
        std::set<D> data;
        detail::generate_random(data, size);
        return schedule<D>(data);
    }
}