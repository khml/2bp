//
// Created by KHML on 2020/05/02.
//

#include <iostream>
#include <stdexcept>

#include <cyan/value.hpp>
#include <cyan/arguments.hpp>

#include "macro_logger.hpp"
#include "parser.hpp"

namespace kind_t = token::kind;

namespace parser
{
    static void consumeForce(token::Container& container, kind_t::Kind kind)
    {
        if (container.consume(kind))
            return;

        STD_ERR_LOG("Expected Token : " << kind_t::fromTokenKind(kind));
        throw std::runtime_error("Expected Token : " + kind_t::fromTokenKind(kind));
    }

    static cyan::Type getType(token::Token& token)
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

    cyan::Expression primary(token::Container& container)
    {
        /*
         * primary = identifier ( "(" sum ")" )
         */

        LOG_DEBUG("primary");

        if (!container.next(kind_t::PARENTHESIS_LEFT))
            return identifier(container);

        auto name = container.consume().value;

        container.consume(kind_t::PARENTHESIS_LEFT);

        cyan::Arguments args;
        args << sum(container);

        consumeForce(container, kind_t::PARENTHESISE_RIGHT);

        if (name == "print")
            return args[0].cout().endl();

        return cyan::createCallee(name, args);
    }

    cyan::Expression priority(token::Container& container)
    {
        /*
         * priority = primary | “(“ sum “)”
         */

        LOG_DEBUG("priority");

        if (container.consume(kind_t::PARENTHESIS_LEFT))
        {
            auto result = sum(container);
            consumeForce(container, kind_t::PARENTHESISE_RIGHT);
            return result.parenthesis();
        }

        return primary(container);
    }

    cyan::Expression unary(token::Container& container)
    {
        /*
         * unary = ( "+" | "-" ) priority
         */

        LOG_DEBUG("unary");

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

        LOG_DEBUG("mul");

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

        LOG_DEBUG("sum");

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

        LOG_DEBUG("identifier");

        auto& token = container.consume();
        auto type = getType(token);
        return cyan::xpr(cyan::Literal(type, token.value));
    }

    cyan::Expression statement(token::Container& container)
    {
        /*
         * statement = sum ";"
         */

        LOG_DEBUG("statement");

        auto result = sum(container);
        consumeForce(container, kind_t::SEMICOLON);
        return result;
    }

    cyan::CodeBlock code(token::Container& container)
    {
        /*
         * code = statement*
         */

        LOG_DEBUG("code");

        auto codeBlock = cyan::CodeBlock();

        while (container.hasNext())
            codeBlock << statement(container);

        return codeBlock;
    }
}