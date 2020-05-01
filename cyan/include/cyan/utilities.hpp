//
// Created by KHML on 2020/04/17.
//

#ifndef CYAN_UTILITIES_HPP
#define CYAN_UTILITIES_HPP

#include <cstddef>
#include <string>
#include <vector>

#include <cyan/type.hpp>

namespace cyan
{
    std::string indent(size_t depth);

    bool isNumber(const Type& type);

    void mergeVector(std::vector<std::string>& to, std::vector<std::string>& from);

    void mergeVector(std::vector<std::string>& to, std::vector<std::string>&& from);

    bool createDir(const std::string& directoryName);

    bool createDir(std::string&& directoryName);

    std::string toUpper(const std::string& str);

    namespace config
    {
        constexpr size_t indentSize = 4;
    }
}

#endif //CYAN_UTILITIES_HPP
