//
// Created by KHML on 2020/05/02.
//

#include "container.hpp"

namespace token
{

    Container::Container(std::vector<Token>& tokens) :tokens(tokens)
    {}

    void Container::reset()
    {
        indicator = 0;
    }

    bool Container::hasNext()
    {
        return indicator < (tokens.size() - 1);
    }

    Token& Container::consume()
    {
        return tokens[indicator++];
    }

    bool Container::consume(token::kind::Kind kind)
    {
        if (tokens[indicator].kind == kind)
        {
            consume();
            return true;
        }

        return false;
    }

    Token& Container::current()
    {
        return tokens[indicator];
    }

    Token& Container::next()
    {
        return tokens[++indicator];
    }

    bool Container::next(token::kind::Kind kind)
    {
        if(!hasNext())
            return false;

        return tokens[indicator + 1].kind == kind;
    }
}