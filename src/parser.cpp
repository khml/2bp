//
// Created by KHML on 2020/05/02.
//

#include <cyan/value.hpp>

#include "parser.hpp"

namespace kind_t = token::kind;

namespace parser
{
    cyan::Type getType(token::Token& token)
    {
        switch (token.type)
        {
            case token::type::INTEGER:
                return cyan::types::intType();
            case token::type::FLOAT:
                return cyan::types::floatType();
            case token::type::DOUBLE:
                return cyan::types::doubleType();
            case token::type::STRING:
                return cyan::types::stringType();
            default:
                break;
        }
        return cyan::Type(token::type::fromTokenType(token.type));
    }

    cyan::Expression sum(token::Container& container)
    {
        auto result = identifier(container);

        while (container.hasNext())
        {
            if (container.consume(kind_t::ADD))
                result = result.add(identifier(container));
            else if (container.consume(kind_t::SUB))
                result = result.sub(identifier(container));
            else
                break;
        }

        return result;
    }

    cyan::Expression identifier(token::Container& container)
    {
        auto& token = container.consume();
        auto type = getType(token);
        return cyan::xpr(cyan::Literal(type, token.value));
    }
}