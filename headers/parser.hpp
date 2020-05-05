//
// Created by KHML on 2020/05/02.
//

#ifndef BP_PARSER_HPP
#define BP_PARSER_HPP

#include <cyan/code_block.hpp>
#include <cyan/expression.hpp>

#include "container.hpp"

namespace parser
{
    cyan::Expression primary(token::Container& container);

    cyan::Expression priority(token::Container& container);

    cyan::Expression unary(token::Container& container);

    cyan::Expression mul(token::Container& container);

    cyan::Expression sum(token::Container& container);

    cyan::Expression identifier(token::Container& container);

    cyan::Expression statement(token::Container& container);

    cyan::CodeBlock code(token::Container& container);
}

#endif //BP_PARSER_HPP
