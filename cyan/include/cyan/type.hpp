//
// Created by KHML on 2020/04/15.
//

#ifndef CYAN_TYPE_HPP
#define CYAN_TYPE_HPP

#include <string>

namespace cyan
{
    class Type
    {
    public:
        explicit Type(std::string name);

        ~Type();

        const std::string name;
    };

    namespace types
    {
        const Type& voidType();

        const Type& intType();

        const Type& floatType();

        const Type& doubleType();

        const Type& stringType();
    }
}

#endif //CYAN_TYPE_HPP
