//
// Created by KHML on 2020/04/25.
//

#ifndef CYAN_VALUE_LITERAL_HPP
#define CYAN_VALUE_LITERAL_HPP

#include <cyan/value/value.hpp>

namespace cyan
{
    class Literal : public Value
    {
    public:
        explicit Literal(int num);

        explicit Literal(float num);

        explicit Literal(double num);

        explicit Literal(const std::string& str);

        explicit Literal(const std::string&& str);

        Literal(const Type& type, const std::string& literal);

        Literal(Type&& type, std::string&& literal);

        ~Literal() override;

        std::string value() const override;

        std::unique_ptr<Value> ptr() const override;

    protected:
        const std::string literal;

        const std::string text;
    };
}

#endif //CYAN_VALUE_LITERAL_HPP
