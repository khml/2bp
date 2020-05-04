//
// Created by KHML on 2020/01/29.
//

#ifndef BLUEPRINT_TOKENTYPE_HPP
#define BLUEPRINT_TOKENTYPE_HPP

#include <string>

namespace token
{
    namespace type
    {
        enum Type
        {
        INTEGER,
        FLOAT,
        DOUBLE,
        STRING,
        IDENTIFIER,
        OPERATOR,
        };

        bool isDigit(const std::string& str);

        bool isFloat(const std::string& str);

        bool isDouble(const std::string& str);

        bool isIdentifier(const std::string& str);

        Type toType(const std::string& str);

        std::string fromTokenType(Type val);
    }

}

#endif //BLUEPRINT_TOKENTYPE_HPP
