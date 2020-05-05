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
/*

 code = statements*
 statements = expression | "{" statements* "}"
 expression = sum ";"
 sum = mul ( “+” mul | “-“ mul )*
 mul = unary ( “*” unary | “/“  unary | “%” unary )*
 unary = ( "+" | "-" ) priority
 priority = primary | “(“ sum “)”
 primary = identifier ( "(" sum ")" )
 identifier = [_a-zA-Z][_a-zA-Z0-9]? | [0-9] ( "." [0-9]+ ) ( "f" )

 */
    cyan::CodeBlock code(token::Container& container);

    cyan::CodeBlock statements(token::Container& container);

    cyan::Expression expression(token::Container& container);

    cyan::Expression sum(token::Container& container);

    cyan::Expression mul(token::Container& container);

    cyan::Expression unary(token::Container& container);

    cyan::Expression priority(token::Container& container);

    cyan::Expression primary(token::Container& container);

    cyan::Expression identifier(token::Container& container);
}

#endif //BP_PARSER_HPP
