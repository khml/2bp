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

    cyan::Expression priority(token::Container& container)
    {
        if (container.consume(kind_t::PARENTHESIS_LEFT))
        {
            auto result = sum(container);
            if (!container.consume(kind_t::PARENTHESISE_RIGHT))
                throw "Expected PARENTHESISE_RIGHT";
            return result.parenthesis();
        }

        return identifier(container);
    }

    cyan::Expression mul(token::Container& container)
    {
        auto result = priority(container);
        while (container.hasNext())
        {
            if (container.consume(kind_t::ASTERISK))
                result = result.mul(priority(container));
            else if (container.consume(kind_t::SLASH))
                result = result.div(priority(container));
            else if (container.consume(kind_t::PERCENT))
                result = result.mod(priority(container));
            else
                break;
        }
        return result;
    }

    cyan::Expression sum(token::Container& container)
    {
        auto result = mul(container);

        while (container.hasNext())
        {
            if (container.consume(kind_t::ADD))
                result = result.add(mul(container));
            else if (container.consume(kind_t::SUB))
                result = result.sub(mul(container));
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