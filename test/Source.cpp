#include <iostream>
#include <tuple>

#include "quants_date/binary.h"
#include "quants_date/builder.h"
#include "quants_date/date.h"
#include "quants_date/date_range.h"
#include "quants_date/unary.h"

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

void test_compare(const qd::date<Date>& d0, const qd::date<Date>& d1);
void test_unary(const qd::date<Date>& d);
void test_binary(const qd::date_range<Date>& range);

int main()
{
    test_compare(
        qd::create_date<Date>(2000, 2, 29),
        qd::create_date<Date>(2000, 5, 1));
    test_compare(
        qd::create_date<Date>(2000, 2, 29),
        qd::create_date<Date>(2000, 2, 29));

    test_unary(qd::create_date<Date>(2000, 2, 29));
    test_unary(qd::create_date<Date>(2013, 6, 1));

    const auto r = qd::create_date_range(
        qd::create_date<Date>(2000u, 1u, 15u),
        qd::create_date<Date>(2000u, 4u, 15u));

    test_binary(r);

    return 0;
}

void test_compare(const qd::date<Date>& d0, const qd::date<Date>& d1)
{
    std::cout << std::boolalpha << (d0 < d1) << std::endl;
    std::cout << std::boolalpha << (d0 > d1) << std::endl;
    std::cout << std::boolalpha << (d0 == d1) << std::endl;
    std::cout << std::boolalpha << (d0 != d1) << std::endl;
    std::cout << std::boolalpha << (d0 <= d1) << std::endl;
    std::cout << std::boolalpha << (d0 >= d1) << std::endl;
    return;
}

void test_unary(const qd::date<Date>& d)
{
    std::cout << qd::to_string<'-'>(d) << std::endl;
    std::cout << qd::to_string<'-'>(qd::add_day(d, 365)) << std::endl;
    std::cout << qd::to_string<'-'>(qd::add_week(d, 2)) << std::endl;
    std::cout << qd::to_string<'-'>(qd::add_month(d, 1)) << std::endl;
    std::cout << qd::to_string<'-'>(qd::add_year(d, 3)) << std::endl;
    std::cout << qd::last_day_of_month(d) << std::endl;
    std::cout << qd::to_serial_value(d) << std::endl;
    std::cout << std::boolalpha << qd::is_leap_year(d) << std::endl;
}

void test_binary(const qd::date_range<Date>& range)
{
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
