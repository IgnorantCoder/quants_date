#include <iostream>
#include <tuple>

#include "quants_date/builder.h"

#include "quants_date/date.h"
#include "quants_date/date_range.h"
#include "quants_date/schedule.h"

#include "quants_date/unary.h"
#include "quants_date/binary.h"
#include "quants_date/scheduler.h"

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

void test_compare();
void test_unary();
void test_binary();
void test_schedule_modifier();
void test_schedule_selector();

int main()
{
    test_compare();
    test_unary();
    test_binary();
    test_schedule_modifier();
    test_schedule_selector();

    return 0;
}

void test_compare()
{
    {
        const auto d0 = qd::create_date<Date>(2000, 2, 29);
        const auto d1 = qd::create_date<Date>(2000, 5, 1);

        std::cout << std::boolalpha << (d0 < d1) << std::endl;
        std::cout << std::boolalpha << (d0 > d1) << std::endl;
        std::cout << std::boolalpha << (d0 == d1) << std::endl;
        std::cout << std::boolalpha << (d0 != d1) << std::endl;
        std::cout << std::boolalpha << (d0 <= d1) << std::endl;
        std::cout << std::boolalpha << (d0 >= d1) << std::endl;
    }

    {
        const auto d0 = qd::create_date<Date>(2000, 2, 29);
        const auto d1 = qd::create_date<Date>(2000, 2, 29);

        std::cout << std::boolalpha << (d0 < d1) << std::endl;
        std::cout << std::boolalpha << (d0 > d1) << std::endl;
        std::cout << std::boolalpha << (d0 == d1) << std::endl;
        std::cout << std::boolalpha << (d0 != d1) << std::endl;
        std::cout << std::boolalpha << (d0 <= d1) << std::endl;
        std::cout << std::boolalpha << (d0 >= d1) << std::endl;
    }

    return;
}

void test_unary()
{
    {
        const auto d = qd::create_date<Date>(2000, 2, 29);
        std::cout << qd::to_string<'-'>(d) << std::endl;
        std::cout << qd::to_string<'-'>(qd::add_day(d, 365)) << std::endl;
        std::cout << qd::to_string<'-'>(qd::add_week(d, 2)) << std::endl;
        std::cout << qd::to_string<'-'>(qd::add_month(d, 1)) << std::endl;
        std::cout << qd::to_string<'-'>(qd::add_year(d, 3)) << std::endl;
        std::cout << qd::last_day_of_month(d) << std::endl;
        std::cout << qd::to_serial_value(d) << std::endl;
        std::cout << std::boolalpha << qd::is_leap_year(d) << std::endl;
    }

    {
        const auto d = qd::create_date<Date>(2013, 6, 1);
        std::cout << qd::to_string<'-'>(d) << std::endl;
        std::cout << qd::to_string<'-'>(qd::add_day(d, 365)) << std::endl;
        std::cout << qd::to_string<'-'>(qd::add_week(d, 2)) << std::endl;
        std::cout << qd::to_string<'-'>(qd::add_month(d, 1)) << std::endl;
        std::cout << qd::to_string<'-'>(qd::add_year(d, 3)) << std::endl;
        std::cout << qd::last_day_of_month(d) << std::endl;
        std::cout << qd::to_serial_value(d) << std::endl;
        std::cout << std::boolalpha << qd::is_leap_year(d) << std::endl;
    }

    {
        std::cout << qd::to_serial_value(qd::create_min<Date>()) << std::endl;
        std::cout << qd::to_serial_value(qd::create_max<Date>()) << std::endl;
    }

    return;
}

void test_binary()
{
    {
        const auto range = qd::create_date_range(
            qd::create_date<Date>(2000u, 1u, 15u),
            qd::create_date<Date>(2000u, 4u, 15u));

        std::cout << qd::count_days(range) << std::endl;
        std::cout << qd::year_fraction_actual_360(range) << std::endl;
        std::cout << qd::year_fraction_actual_365_fixed(range) << std::endl;
        std::cout << qd::year_fraction_actual_actual(range) << std::endl;
        std::cout << qd::year_fraction_one_one(range) << std::endl;
        std::cout << qd::year_fraction_30_360_bond_basis(range) << std::endl;
        std::cout << qd::year_fraction_30e_360(range) << std::endl;

        const auto additional = qd::create_date<Date>(2000u, 4u, 15u);
        std::cout << qd::year_fraction_30e_360_isda(range, additional) << std::endl;
        std::cout << qd::year_fraction_actual_365l(range, "quarterly") << std::endl;
        std::cout << qd::year_fraction_actual_actual_icma(range, additional, "quarterly") << std::endl;
    }

    return;
}

void test_schedule_modifier()
{
    {
        const auto schedule0 = qd::generate_random<Date>(5);
        const auto schedule1 = qd::generate_random<Date>(3);
        const auto ret = qd::concat_copy(schedule0, schedule1);
    }

    return;
}

void test_schedule_selector()
{
    return;
}
