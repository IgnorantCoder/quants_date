#include <iostream>

#include "quants_date/builder/date_builder.h"
#include "quants_date/date.h"
#include "quants_date/unary.h"

#include "quants_date/mpl/is_leap_year.h"
#include "quants_date/mpl/generate_array.h"
#include "quants_date/mpl/the_number_of_days_data.h"

class Date {
public:
    Date() : _y(), _m(), _d() {}
    Date(const std::size_t y, const std::size_t m, const std::size_t d) : _y(y), _m(m), _d(d) {}
    std::size_t year() const { return _y; }
    std::size_t month() const { return _m; }
    std::size_t day() const { return _d; }
    bool operator< (const Date& other) const {
        if (_y < other._y) { return true; }
        if (_y > other._y) { return false; }
        if (_m < other._m) { return true; }
        if (_m > other._m) { return false; }
        return _d < other._d;
    }

private:
    std::size_t _y;
    std::size_t _m;
    std::size_t _d;
};

namespace qd { namespace builder {
    template <>
    struct create_null_object_traits<Date> {
        using result_type = date<Date>;
        static result_type apply()
        {
            Date&& nullobj = {};
            return result_type(std::move(nullobj));
        }
    };

    template <>
    struct create_from_ymd_traits<Date> {
        using result_type = date<Date>;
        static result_type apply(
            const std::size_t y,
            const std::size_t m,
            const std::size_t d)
        {
            Date&& data = { y, m, d };
            return result_type(std::move(data));
        }
    };
}}

int main()
{
    //const auto d0 = qd::create_date<Date>(2000, 2, 29);
    //const auto d1 = qd::create_date<Date>(2000, 5, 31);
    //std::cout << qd::to_string<'-'>(d0) << std::endl;
    //std::cout << std::boolalpha << qd::is_leap_year(d0) << std::endl;
    //std::cout << qd::last_day_of_month(d0) << std::endl;
    //std::cout << qd::to_string<'-'>(qd::add_day(d1, 365)) << std::endl;
    //std::cout << qd::to_string<'-'>(qd::add_week(d1, 2)) << std::endl;
    //std::cout << qd::to_string<'-'>(qd::add_month(d1, 1)) << std::endl;
    //std::cout << qd::to_string<'-'>(qd::add_year(d0, 3)) << std::endl;

    const auto d0 = qd::create_date<Date>(1900, 1, 1);
    std::size_t buf;
    for (int n = 0; n < 3; ++n) {
        for (int i = 0; i < 365 * 250; ++i) {
            const auto tmp = qd::add_day(d0, i);
            buf = qd::to_serial_value(tmp);
        }
    }

    //for (std::size_t i = 1; i < 365 * 250; ++i) {
    //    const auto tmp = qd::create_date<Date>(i);
    //    std::cout << qd::to_string<'/'>(tmp) << "," << i << std::endl;
    //}


    return 0;
}