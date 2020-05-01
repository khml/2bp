//
// Created by KHML on 2020/04/19.
//

#ifndef CYAN_EXPRESSION_HPP
#define CYAN_EXPRESSION_HPP

#include <string>

#include <cyan/type.hpp>
#include <cyan/value/value.hpp>
#include <cyan/value/variable.hpp>

namespace cyan
{
    class Expression
    {
    public:
        Expression();

        explicit Expression(const Value& value);

        explicit Expression(Value&& value);

        explicit Expression(Variable& value);

        Expression(const Expression& orig);

        ~Expression();

        std::string operator()() const;

        Expression& set(Variable& value);

        Expression& set(Variable&& value);

        Expression& assign(const Value& value);

        Expression& assign(Value&& value);

        Expression& add(const Value& value);

        Expression& add(Value&& value);

        Expression& sub(const Value& value);

        Expression& sub(Value&& value);

        Expression& mul(const Value& value);

        Expression& mul(Value&& value);

        Expression& div(const Value& value);

        Expression& div(Value&& value);

        Expression& mod(const Value& value);

        Expression& mod(Value&& value);

        Expression& parenthesis();

        Expression& equal(const Value& value);

        Expression& equal(Value&& value);

        Expression& preIncrement();

        Expression& preDecrement();

        Expression& postIncrement();

        Expression& postDecrement();

        Expression& andOp(const Value& value);

        Expression& andOp(Value&& value);

        Expression& orOp(const Value& value);

        Expression& orOp(Value&& value);

        Expression& notOp();

        Expression& cast(const Type& type);

        Expression& cast(const Type&& type);

        Expression& grater(const Value& value);

        Expression& grater(Value&& value);

        Expression& lesser(const Value& value);

        Expression& lesser(Value&& value);

        Expression& graterThan(const Value& value);

        Expression& graterThan(Value&& value);

        Expression& lesserThan(const Value& value);

        Expression& lesserThan(Value&& value);

        Expression& move();

        Expression& dot(const std::string& memberName);

        Expression& dot(std::string&& memberName);

        Expression& arrow(const std::string& memberName);

        Expression& arrow(std::string&& memberName);

        Expression& operator<<(const Value& value);

        Expression& operator<<(Value&& value);

        Expression& operator>>(const Value& value);

        Expression& operator>>(Value&& value);

        Expression& cin();

        Expression& cout();

        Expression& cerr();

        Expression& endl();

    protected:
        std::string expression;

        void pre(std::string&& op);

        void post(std::string&& op);

        void binaryOp(std::string&& op, const Value& value);
    };
}

#endif //CYAN_EXPRESSION_HPP
