//
// Created by KHML on 2020/04/23.
//

#ifndef CYAN_VALUE_VARIABLES_HPP
#define CYAN_VALUE_VARIABLES_HPP

#include <string>
#include <vector>

#include <cyan/value/variable.hpp>

namespace cyan
{
    class StructBlock;

    class Variables
    {
    public:
        Variables();

        ~Variables();

        std::string args() const;

        std::string implArgs() const;

        std::string callee() const;

        void append(Variable& value);

        void append(Variable&& value);

        Variables& operator<<(Variable& value);

        Variables& operator<<(Variable&& value);

        const Variable& operator[](size_t idx) const;

        void clear();

        friend StructBlock;

    protected:
        std::string _args;
        std::string _impl_args;
        std::string _callee;
        std::vector<Variable> variables;
    };
}

#endif //CYAN_VALUE_VARIABLES_HPP
