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
         * primary = identifier ( "(" condition ")" )
         */

        LOG_DEBUG("primary");

        if (!container.next(kind_t::PARENTHESIS_LEFT))
            return identifier(container);

        auto name = container.consume().value;

        container.consume(kind_t::PARENTHESIS_LEFT);

        cyan::Arguments args;
        args << condition(container);

        consumeForce(container, kind_t::PARENTHESISE_RIGHT);

        if (name == "print")
            return args[0].cout().endl();

        return cyan::createCallee(name, args);
    }

    cyan::Expression priority(token::Container& container)
    {
        /*
         * priority = primary | “(“ condition “)”
         */

        LOG_DEBUG("priority");

        if (container.consume(kind_t::PARENTHESIS_LEFT))
        {
            auto result = condition(container);
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

    cyan::Expression equation(token::Container& container)
    {
        /*
         * equation = ( "return" ) condition ";"
         */

        LOG_DEBUG("equation");

        cyan::Expression result;

        if (container.consume(kind_t::RETURN))
            result = condition(container).ret();
        else
            result = condition(container);
        consumeForce(container, kind_t::SEMICOLON);
        return result;
    }

    cyan::CodeBlock code(token::Container& container, cyan::Module& module)
    {
        /*
         * code = statement*
         */

        LOG_DEBUG("code");

        auto block = cyan::CodeBlock();

        while (container.hasNext())
        {
            if (container.current(kind_t::BRACE_LEFT))
                block << statements(container, module);
            else
                block << expression(container, module);
        }

        return block;
    }

    cyan::CodeBlock statements(token::Container& container, cyan::Module& module)
    {
        /*
         * statements = expression | "{" statements* "}"
         */

        LOG_DEBUG("statements");

        auto block = cyan::CodeBlock();

        consumeForce(container, kind_t::BRACE_LEFT);

        while (container.hasNext())
        {
            if (container.current(kind_t::BRACE_LEFT))
                block << statements(container, module);
            else if (container.consume(kind_t::BRACE_RIGHT))
                break;
            else
                block << expression(container, module);
        }

        return block;
    }

    cyan::Expression expression(token::Container& container, cyan::Module& module)
    {
        /*
         * expression = equation | assignment | function
         */

        LOG_DEBUG("expression");

        if ((container.current(kind_t::IDENTIFIER) && container.next(kind_t::COLON)) ||
            (container.current(kind_t::IDENTIFIER) && container.next(kind_t::EQUAL)))
        {
            // assignment
            return assignment(container);
        }
        else if (container.current(kind_t::FUNCTION))
        {
            // function
            function(container, module);
            return cyan::Expression();
        }
        else
        {
            // equation
            return equation(container);
        }
    }

    cyan::Expression assignment(token::Container& container)
    {
        /*
         * assignment = identifier ( ":" type ) “=“ equation
         */

        LOG_DEBUG("assignment");

        const auto name = container.consume().value;

        std::string type = "auto";
        if (container.consume(kind_t::COLON))
            type = container.consume().value;

        auto var = cyan::xpr(cyan::Variable(name, cyan::Type(type)));

        consumeForce(container, kind_t::EQUAL);

        return var.assign(equation(container));
    }

    cyan::Expression comparison(token::Container& container)
    {
        /*
         * comparison = sum ( [ "==", <", "<=", ">=", ">" ] sum )*
         */

        LOG_DEBUG("comparison");

        auto result = sum(container);

        while (container.hasNext())
        {
            if (container.consume(kind_t::EQUIVALENCE))
                result.equal(sum(container));
            else if (container.consume(kind_t::LESSER_THAN))
                result.lesserThan(sum(container));
            else if (container.consume(kind_t::LESSER))
                result.lesser(sum(container));
            else if (container.consume(kind_t::GRATER_THAN))
                result.graterThan(sum(container));
            else if (container.consume(kind_t::GRATER))
                result.grater(sum(container));
            else
                break;
        }

        return result;
    }

    cyan::Expression condition(token::Container& container)
    {
        /*
         * comparison ( “&&” comparison | “||” comparison)*
         */

        LOG_DEBUG("condition");

        auto result = comparison(container);

        while (container.hasNext())
        {
            if (container.consume(kind_t::AND))
                result.andOp(comparison(container));
            else if (container.consume(kind_t::OR))
                result.orOp(comparison(container));
            else
                break;
        }

        return result;
    }

    cyan::Function function(token::Container& container, cyan::Module& module)
    {
        /*
         * "fn" identifier "(" ")" ":" type "{" statements "}"
         */

        LOG_DEBUG("function");

        consumeForce(container, kind_t::FUNCTION);

        auto name = container.consume().value;

        consumeForce(container, kind_t::PARENTHESIS_LEFT);
        consumeForce(container, kind_t::PARENTHESISE_RIGHT);
        consumeForce(container, kind_t::COLON);

        auto type = cyan::Type(container.consume().value);
        cyan::Function func(name, type);
        func() = statements(container, module);

        module << func;

        return func;
    }
}