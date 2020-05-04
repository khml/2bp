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
        /*
         * priority = identifier | “(“ sum “)”
         */
        if (container.consume(kind_t::PARENTHESIS_LEFT))
        {
            auto result = sum(container);
            if (!container.consume(kind_t::PARENTHESISE_RIGHT))
                throw "Expected PARENTHESISE_RIGHT";
            return result.parenthesis();
        }

        return identifier(container);
    }

    cyan::Expression unary(token::Container& container)
    {
        /*
         * unary = ( "+" | "-" ) priority
         */
        auto result = cyan::Expression();
        if (container.consume(kind_t::ADD))
            result.add(priority(container));
        else if (container.consume(kind_t::SUB))
            result.sub(priority(container));
        else
            result = priority(container);

        return result;
    }

    cyan::Expression mul(token::Container& container)
    {
        /*
         * mul = unary ( “*” unary | “/“  unary | “%” unary )*
         */
        auto result = unary(container);
        while (container.hasNext())
        {
            if (container.consume(kind_t::ASTERISK))
                result = result.mul(unary(container));
            else if (container.consume(kind_t::SLASH))
                result = result.div(unary(container));
            else if (container.consume(kind_t::PERCENT))
                result = result.mod(unary(container));
            else
                break;
        }
        return result;
    }

    cyan::Expression sum(token::Container& container)
    {
        /*
         * sum = mul ( “+” mul | “-“ mul )*
         */
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
        /*
         * identifier = [_a-zA-Z][_a-zA-Z0-9]? | [0-9] ( "." [0-9]+ ) ( "f" )
         */
        auto& token = container.consume();
        auto type = getType(token);
        return cyan::xpr(cyan::Literal(type, token.value));
    }
}