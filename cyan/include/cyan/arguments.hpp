//
// Created by KHML on 2020/04/23.
//

#ifndef CYAN_ARGUMENTS_HPP
#define CYAN_ARGUMENTS_HPP

#include <string>
#include <memory>
#include <vector>

#include <cyan/value.hpp>

namespace cyan
{
    class Arguments
    {
    public:
        Arguments();

        ~Arguments();

        std::string operator()() const;

        Arguments& append(const Value& value);

        Arguments& append(Value&& value);

        Arguments& operator<<(const Value& value);

        Arguments& operator<<(Value&& value);

        Arguments& clear();

    protected:
        std::vector<std::unique_ptr<Value>> args;
    };
}

#endif //CYAN_ARGUMENTS_HPP
