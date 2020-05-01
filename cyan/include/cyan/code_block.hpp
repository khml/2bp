//
// Created by KHML on 2020/04/17.
//

#ifndef CYAN_CODE_BLOCK_HPP
#define CYAN_CODE_BLOCK_HPP

#include <string>
#include <vector>

#include <cyan/arguments.hpp>
#include <cyan/expression.hpp>
#include <cyan/value.hpp>
#include <cyan/value/variables.hpp>

namespace cyan
{
    class Function;

    class Control;

    class CodeBlock
    {
    public:
        CodeBlock();

        CodeBlock(const CodeBlock& orig);

        ~CodeBlock();

        std::vector<std::string> codeGen(size_t indentSize) const;

        void declareVariable(Variable& var);

        CodeBlock& operator<<(Variable& var);

        CodeBlock& operator<<(const CodeBlock& codeBlock);

        CodeBlock& operator<<(CodeBlock&& codeBlock);

        CodeBlock& operator<<(const Expression& expression);

        CodeBlock& operator<<(Expression&& expression);

        CodeBlock& operator<<(const Control& control);

        CodeBlock& operator<<(Control&& control);

        void createAdd(Value& right, Value& left, Variable& result);

        void createSub(Value& right, Value& left, Variable& result);

        void createMul(Value& right, Value& left, Variable& result);

        void createDiv(Value& right, Value& left, Variable& result);

        void createMod(Value& right, Value& left, Variable& result);

        void createRetValue(Value& value);

        void createStdOut(const Value& value);

        void createStdOut(Value&& value);

        void createStdOut(const Expression& value);

        void createStdOut(Expression&& value);

        void createStdErrOut(const Value& value);

        void createStdErrOut(Value&& value);

        void createStdErrOut(const Expression& value);

        void createStdErrOut(Expression&& value);

        void createCallee(const Function& function);

        void createCallee(const Function& function, const Arguments& args);

        void createCallee(const Function& function, const Variables& args);

        void createCallee(const Function& function, Variable& result);

        void createCallee(const Function& function, const Arguments& args, Variable& result);

        void createCallee(const Function& function, const Variables& args, Variable& result);

    protected:
        std::vector<std::string> lines;

        void createArithmeticOp(std::string&& op, Value& right, Value& left, Variable& result);

        void createCallee(const Function& function, std::string&& calleeArgs, std::string&& prefix = "");
    };
}

#endif //CYAN_CODE_BLOCK_HPP
