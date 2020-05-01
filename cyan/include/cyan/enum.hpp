//
// Created by KHML on 2020/04/18.
//

#ifndef CYAN_ENUM_BLOCK_HPP
#define CYAN_ENUM_BLOCK_HPP

#include <string>
#include <tuple>
#include <vector>

#include <cyan/type.hpp>

namespace cyan
{
    class EnumBlock
    {
    public:
        explicit EnumBlock(std::string tag);

        EnumBlock(std::string tag, const std::vector<std::string>& items, int initialValue);

        EnumBlock(const std::string& tag, const std::vector<std::string>& items);

        EnumBlock(std::string tag, const std::vector<std::tuple<std::string, int>>& items);

        virtual ~EnumBlock();

        std::vector<std::string> codeGen(size_t indentSize) const;

        const Type type;

        void append(const std::string& item);

        void append(std::string&& item);

        void append(const std::string& item, int number);

        void append(const std::string&& item, int number);

        EnumBlock& operator<<(const std::string& item);

        EnumBlock& operator<<(std::string&& item);

    protected:
        std::vector<std::string> lines;
    };
}

#endif //CYAN_ENUM_BLOCK_HPP
