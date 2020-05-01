//
// Created by KHML on 2020/04/25.
//

#ifndef CYAN_CONTROL_FOR_CONTROL_HPP
#define CYAN_CONTROL_FOR_CONTROL_HPP

#include <cyan/control/control.hpp>
#include <cyan/code_block.hpp>
#include <cyan/expression.hpp>
#include <cyan/value/variable.hpp>

namespace cyan
{
    class ForControl : public Control
    {
    public:
        ForControl();

        ForControl(Expression&& init, Expression& condition, Expression& iterExpr);

        ForControl(Variable& init, Expression& condition, Expression& iterExpr);

        ForControl(Variable& init, Expression& vectorExp);

        ForControl(Variable& iter, Variable& vectorVar);

        ~ForControl() override;

        std::vector<std::string> codeGen(size_t indentSize) const override;

        CodeBlock& operator()();

        CodeBlock& operator<<(Variable& var);

        CodeBlock& operator<<(const CodeBlock& codeBlock);

        CodeBlock& operator<<(CodeBlock&& codeBlock);

        CodeBlock& operator<<(const Expression& expression);

        CodeBlock& operator<<(Expression&& expression);

        CodeBlock& operator<<(const Control& control);

        CodeBlock& operator<<(Control&& control);

    protected:
        std::string forSentence;
        CodeBlock codeBlock;
    };
}

#endif //CYAN_CONTROL_FOR_CONTROL_HPP
