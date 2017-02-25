#pragma once

#include <string>

#include "quants_date/date.h"
#include "quants_date/unary/unary_expression.h"

namespace qd { namespace unary {
    template <char delim>
    class string_converter : public unary_expression<string_converter<delim>> {
    private:
        using base_type = unary_expression<string_converter>;
        friend class base_type;

    public:
        using result_type = std::string;

    public:
        string_converter();
        result_type get() const;

    private:
        void do_apply(
            const std::size_t y,
            const std::size_t m,
            const std::size_t d) const;

    private:
        mutable result_type _result;
    };

    template<char delim>
    inline string_converter<delim>::string_converter()
        : _result()
    {
    }

    template<char delim>
    inline std::string string_converter<delim>::get() const
    {
        return this->_result;
    }

    template <char delim> inline
    void string_converter<delim>::do_apply(
        const std::size_t y, 
        const std::size_t m, 
        const std::size_t d) const
    {
        this->_result = std::to_string(y)
            + delim + std::to_string(m)
            + delim + std::to_string(d);
    }
}}

namespace qd {
    template<char delim, typename D>
    typename unary::string_converter<delim>::result_type
    to_string(const date<D>& d)
    {
        const unary::string_converter<delim> converter;
        d.accept(converter);
        return converter.get();
    }
}