//
// Created by KHML on 2020/04/25.
//

#ifndef CYAN_CONTROL_CONTROL_HPP
#define CYAN_CONTROL_CONTROL_HPP

#include <string>
#include <vector>

namespace cyan
{
    class Control
    {
    public:
        Control();

        virtual ~Control();

        virtual std::vector<std::string> codeGen(size_t indentSize) const = 0;
    };
}

#endif //CYAN_CONTROL_CONTROL_HPP
