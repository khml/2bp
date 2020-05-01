//
// Created by KHML on 2020/04/25.
//

#ifndef CYAN_VALUE_VARIABLE_HPP
#define CYAN_VALUE_VARIABLE_HPP

#include <cyan/value/value.hpp>
#include <cyan/value/literal.hpp>

namespace cyan
{
    class Aggregate;

    class Expression;

    class Variable : public Value
    {
    public:
        Variable(std::string name, const Type& type);

        Variable(std::string name, const Literal& initValue);

        Variable(std::string&& name, Literal&& initValue);

        Variable(std::string&& name, const Aggregate& initValue);

        ~Variable() override;

        friend void registerVariable(Variable& var);

        std::string value() const override;

        const std::string name;

        std::string declaration() const; // Type name

        std::string initialization() const; // Type name(InitialValue)

        std::string arg() const; // Type name = InitialValue

        std::unique_ptr<Value> ptr() const override;

        Expression operator()() override;

    protected:
        bool registered = false;
        const bool equalInitialization = false;
        const std::string initValue;
    };

    void registerVariable(Variable& var);
}

#endif //CYAN_VALUE_VARIABLE_HPP
