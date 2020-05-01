//
// Created by KHML on 2020/04/24.
//

#ifndef CYAN_CONTROL_WHILE_CONTROL_HPP
#define CYAN_CONTROL_WHILE_CONTROL_HPP

#include <string>
#include <vector>

#include <cyan/control/control.hpp>
#include <cyan/code_block.hpp>
#include <cyan/expression.hpp>

namespace cyan
{
    class WhileControl : public Control
    {
    public:
        WhileControl();

        explicit WhileControl(const Expression& condition);

        explicit WhileControl(Expression&& condition);

        WhileControl(const Expression& condition, const CodeBlock& statements);

        ~WhileControl() override;

        std::vector<std::string> codeGen(size_t indentSize) const override;

        CodeBlock& operator()();

        CodeBlock& operator<<(const CodeBlock& codeBlock);

        CodeBlock& operator<<(CodeBlock&& codeBlock);

        CodeBlock& operator<<(const Expression& expression);

        CodeBlock& operator<<(Expression&& expression);

        CodeBlock& operator<<(const Control& control);

        CodeBlock& operator<<(Control&& control);

    protected:
        Expression condition;
        CodeBlock statements;
    };

    class DoWhileControl : public Control
    {
    public:
        DoWhileControl();

        DoWhileControl(const Expression& condition);

        DoWhileControl(Expression&& condition);

        DoWhileControl(const Expression& condition, const CodeBlock& statements);

        ~DoWhileControl() override;

        std::vector<std::string> codeGen(size_t indentSize) const override;

        CodeBlock& operator()();

        CodeBlock& operator<<(const CodeBlock& codeBlock);

        CodeBlock& operator<<(CodeBlock&& codeBlock);

        CodeBlock& operator<<(const Expression& expression);

        CodeBlock& operator<<(Expression&& expression);

        CodeBlock& operator<<(const Control& control);

        CodeBlock& operator<<(Control&& control);

    protected:
        Expression condition;
        CodeBlock statements;
    };
}

#endif //CYAN_CONTROL_WHILE_CONTROL_HPP
