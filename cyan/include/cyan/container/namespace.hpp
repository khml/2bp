//
// Created by KHML on 2020/04/27.
//

#ifndef CYAN_CONTAINER_NAMESPACE_HPP
#define CYAN_CONTAINER_NAMESPACE_HPP

#include <cstddef>
#include <string>
#include <vector>

#include <cyan/function.hpp>
#include <cyan/enum.hpp>
#include <cyan/struct.hpp>

namespace cyan
{
    class NameSpace
    {
    public:
        explicit NameSpace(std::string name);

        ~NameSpace();

        NameSpace& operator<<(const Function& func);

        NameSpace& operator<<(const EnumBlock& enumBlock);

        NameSpace& operator<<(const StructBlock& structBlock);

        NameSpace& operator<<(const NameSpace& nameSpace);

        std::vector<std::string> impl(size_t indentSize) const;

        std::vector<std::string> declares(size_t indentSize) const;

        const std::string name;

    protected:
        std::vector<std::string> gen(size_t indentSize, const std::vector<std::string>& body) const;

        const size_t indentSize = 0;
        std::vector<std::string> lines;
        std::vector<std::string> declarations;
    };
}

#endif //CYAN_CONTAINER_NAMESPACE_HPP
