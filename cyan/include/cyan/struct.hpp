//
// Created by KHML on 2020/04/19.
//

#ifndef CYAN_STRUCT_BLOCK_HPP
#define CYAN_STRUCT_BLOCK_HPP

#include <string>
#include <vector>

namespace cyan
{
    class Variable;

    class Variables;

    class StructBlock
    {
    public:
        explicit StructBlock(std::string tag);

        StructBlock(std::string tag, const std::vector<Variable>& members);

        StructBlock(std::string tag, Variables& members);

        ~StructBlock();

        void append(const Variable& member);

        void append(Variable&& member);

        StructBlock& operator<<(const Variable& member);

        StructBlock& operator<<(Variable&& member);

        std::vector<std::string> codeGen(size_t indentSize) const;

        const Type type;

    protected:
        std::vector<std::string> lines;
    };
}

#endif //CYAN_STRUCT_BLOCK_HPP
