# ReadMe
quants_date is date object wrapper library and has financial engineering utilities.

This library is designed with very strong encapsulation.
For example qd::date that is single date wrapper does not have any getter/setter, you can not use it without through unary_expression.
But, you can add your own function easily with keeping its strong encapsulation if you want.

# single date wrapper
"quants_date/date.h" make you usable qd::date as single date wrapper.
qd::date hold original other date object that need to have following method.
```
class original_date {
public:
    std::size_t year() const;
    std::size_t month() const;
    std::size_t day() const;
}
```
In other words, you can use ordinary date object as qd::date, for example boost::gregorian::date.

## unary
unary for qd::date.
You can use all unary with only including "quants_date/unary.h".

### add
- add_day
- add_week
- add_month
- add_year

### last day of month
- is_last_day_of_month
- last day of month

### leap year
- is_leap_year.h

### convert to
- to_string
- to_serial_value

# date pair wrapper
## binary
