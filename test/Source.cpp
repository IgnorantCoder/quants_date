#include <iostream>

#include "quants_date/date.h"
#include "quants_date/unary.h"

class Date {
public:
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

using basic_date = qd::date<Date>;

int main()
{
    basic_date d0(2100, 2, 1);
    std::cout << qd::to_string<'-'>(d0) << std::endl;
    std::cout << std::boolalpha << qd::is_leap_year(d0) << std::endl;
    std::cout << qd::last_day_of_month(d0) << std::endl;

    return 0;
}