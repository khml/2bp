//
// Created by KHML on 2020/04/01.
//

#include <iostream>
#include <utility>

#include "Token.hpp"

#define MOVE(value) value(std::move((value)))

namespace token
{
    Token::Token(const token::kind::Kind kind, std::string value) :kind(kind), MOVE(value),
        type(token::type::toType(value)), filename(""), row(0)
    {}

    Token::Token(const token::kind::Kind kind, std::string value, token::type::Type type) :kind(kind),
        MOVE(value), type(type), filename(""), row(0)
    {}

    Token::Token(const token::kind::Kind kind, const token::type::Type type) :kind(kind), type(type),
        value(token::kind::fromTokenKind(kind)), filename(""), row(0)
    {}

    Token::Token(const token::Token& orig) :kind(orig.kind), type(orig.type), value(orig.value),
        filename(orig.filename), row(orig.row)
    {}

    Token::Token(const token::kind::Kind kind, std::string value, std::string filename, const uint16_t row)
        :MOVE(kind), MOVE(value), type(token::type::toType(value)), MOVE(filename), row(row)
    {}

    Token::Token(const token::kind::Kind kind, std::string value, token::type::Type type, std::string filename,
        const uint16_t row) :MOVE(kind), MOVE(value), MOVE(type), MOVE(filename), row(row)
    {}

    Token::Token(const token::kind::Kind kind, token::type::Type type, std::string filename, const uint16_t row)
        :MOVE(kind), value(token::kind::fromTokenKind(kind)), MOVE(type), MOVE(filename), row(row)
    {}

    Token::~Token()
    = default;

    void Token::print()
    {
        std::cerr << value << " | " << token::kind::fromTokenKind(kind)
                  << " | " << token::type::fromTokenType(type) << std::endl;
    }
}