//
// Created by KHML on 2020/04/15.
//

#ifndef CYAN_FUNCTION_HPP
#define CYAN_FUNCTION_HPP

#include <string>
#include <memory>
#include <vector>

#include <cyan/type.hpp>
#include <cyan/value.hpp>
#include <cyan/value/variables.hpp>
#include <cyan/code_block.hpp>

namespace cyan
{
    class Function
    {
    public:
        Function(std::string funcName, const Type& type);

        Function(std::string funcName, const Type& type, Variable& arg);

        Function(std::string funcName, Type&& type, Variable& arg);

        Function(std::string funcName, const Type& type, std::vector<Variable>& args);

        Function(std::string funcName, Type&& type, std::vector<Variable>& args);

        Function(std::string funcName, const Type& type, const Variables& variables);

        Function(std::string funcName, Type&& type, const Variables& variables);

        ~Function();

        std::vector<std::string> codeGen(size_t indentSize) const;

        std::string declaration() const;

        Variables& args();

        CodeBlock& operator()();

        CodeBlock& operator<<(const Expression& expression);

        CodeBlock& operator<<(Expression&& expression);

        Variables& operator<<(Variable& value);

        Variables& operator<<(Variable&& value);

        CodeBlock& operator<<(const CodeBlock& codeBlock);

        CodeBlock& operator<<(CodeBlock&& codeBlock);

        CodeBlock& operator<<(const Control& control);

        CodeBlock& operator<<(Control&& control);

        const Type type;
        const std::string name;

    protected:
        Variables arguments;
        CodeBlock codeBlock;
    };
}

#endif //CYAN_FUNCTION_HPP
