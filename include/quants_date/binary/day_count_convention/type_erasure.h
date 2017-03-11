#pragma once

#include <cstddef>
#include <memory>

#include "quants_date/binary/fwd.h"
#include "quants_date/binary/day_count_fraction.h"
#include "quants_date/binary/day_count_convention/day_count_convention_expression.h"

namespace qd { namespace binary { namespace dcc {
    namespace detail {
        class invoker {
        public:
            virtual ~invoker();

        public:
            double invoke(
                const std::size_t from_y,
                const std::size_t from_m,
                const std::size_t from_d,
                const std::size_t to_y,
                const std::size_t to_m,
                const std::size_t to_d) const;

        private:
            virtual double do_invoke(
                const std::size_t from_y,
                const std::size_t from_m,
                const std::size_t from_d,
                const std::size_t to_y,
                const std::size_t to_m,
                const std::size_t to_d) const = 0;

        };

        inline invoker::~invoker()
        {
        }

        inline double invoker::invoke(
            const std::size_t from_y,
            const std::size_t from_m,
            const std::size_t from_d,
            const std::size_t to_y,
            const std::size_t to_m,
            const std::size_t to_d) const
        {
            return this->do_invoke(from_y, from_m, from_d, to_y, to_m, to_d);
        }

        template <typename T>
        class holder : public invoker {
        public:
            using inner_type = T;

        public:
            template <typename E>
            holder(const E& original) 
                : _original(day_count_fraction<inner_type>(original))
            {}

        private:
            virtual double do_invoke(
                const std::size_t from_y, 
                const std::size_t from_m, 
                const std::size_t from_d, 
                const std::size_t to_y,
                const std::size_t to_m, 
                const std::size_t to_d) const override
            {
                _original.apply(from_y, from_m, from_d, to_y, to_m, to_d);
                return _original.get();
            }

        private:
            day_count_fraction<inner_type> _original;
        };
    }

    class type_erased_wrapper
        : public day_count_convention_expression<type_erased_wrapper> {
        friend class day_count_fraction<type_erased_wrapper>;

    public:
        template <typename E>
        type_erased_wrapper(const day_count_convention_expression<E>& original);
        type_erased_wrapper(type_erased_wrapper&& other);

    private:
        double calculate_day_count(
            const std::size_t from_y,
            const std::size_t from_m,
            const std::size_t from_d,
            const std::size_t to_y,
            const std::size_t to_m,
            const std::size_t to_d) const;

    private:
        std::unique_ptr<const detail::invoker> _original;
    };

    template<typename E>
    inline type_erased_wrapper::type_erased_wrapper(
        const day_count_convention_expression<E>& original)
        : _original(std::make_unique<const detail::holder<E>>(original()))
    {
    }

    inline type_erased_wrapper::type_erased_wrapper(
        type_erased_wrapper && other)
        : _original(std::move(other._original))
    {
    }

    double type_erased_wrapper::calculate_day_count(
        const std::size_t from_y, 
        const std::size_t from_m,
        const std::size_t from_d, 
        const std::size_t to_y, 
        const std::size_t to_m, 
        const std::size_t to_d) const
    {
        return this->_original->invoke(
            from_y, from_m, from_d,
            to_y, to_m, to_d);
    }
} } }