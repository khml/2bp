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

    bool createDir(const std::string& directoryName);

    bool createDir(std::string&& directoryName);

    std::string toUpper(const std::string& str);

    template <typename T>
    constexpr void mergeVector(std::vector<T>& to, std::vector<T>& from);

    template <typename T>
    constexpr void mergeVector(std::vector<T>& to, std::vector<T>&& from);

    namespace config
    {
        constexpr size_t indentSize = 4;
    }
}

#include <cyan/impl/utilities.hpp>

#endif //CYAN_UTILITIES_HPP
