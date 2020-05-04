//
// Created by KHML on 2020/05/02.
//

#ifndef BP_PARSER_HPP
#define BP_PARSER_HPP

#include <cyan/expression.hpp>

#include "container.hpp"

namespace parser
{
    cyan::Expression mul(token::Container& container);

    cyan::Expression sum(token::Container& container);

    cyan::Expression identifier(token::Container& container);
}

#endif //BP_PARSER_HPP
