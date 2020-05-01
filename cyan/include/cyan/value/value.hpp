//
// Created by KHML on 2020/04/25.
//

#ifndef CYAN_VALUE_VALUE_HPP
#define CYAN_VALUE_VALUE_HPP

#include <string>
#include <memory>

#include <cyan/type.hpp>

namespace cyan
{
    class Expression;

    class Value
    {
    public:
        explicit Value(const Type& type);

        explicit Value(const Type&& type);

        virtual ~Value();

        const Type type;

        virtual std::string value() const = 0;

        virtual std::unique_ptr<Value> ptr() const = 0;

        virtual Expression operator()();
    };
}

#endif //CYAN_VALUE_VALUE_HPP
