//
// Created by KHML on 2020/05/02.
//

#ifndef BP_PARSER_HPP
#define BP_PARSER_HPP

#include <cyan/arguments.hpp>
#include <cyan/code_block.hpp>
#include <cyan/control.hpp>
#include <cyan/expression.hpp>
#include <cyan/function.hpp>
#include <cyan/module.hpp>

#include "container.hpp"

namespace parser
{
    cyan::CodeBlock code(token::Container& container, cyan::Module& module);

    cyan::CodeBlock statement(token::Container& container, cyan::Module& module);

    cyan::CodeBlock statements(token::Container& container, cyan::Module& module);

    cyan::CodeBlock expression(token::Container& container, cyan::Module& module);

    cyan::Function function(token::Container& container, cyan::Module& module);

    cyan::IfControl ifControl(token::Container& container, cyan::Module& module);

    cyan::ForControl forControl(token::Container& container, cyan::Module& module);

    cyan::Expression equation(token::Container& container);

    cyan::Expression assignment(token::Container& container);

    cyan::Expression condition(token::Container& container);

    cyan::Expression comparison(token::Container& container);

    cyan::Expression sum(token::Container& container);

    cyan::Expression mul(token::Container& container);

    cyan::Expression unary(token::Container& container);

    cyan::Expression priority(token::Container& container);

    cyan::Expression increment(token::Container& container);

    cyan::Expression primary(token::Container& container);

    cyan::Variables defArgs(token::Container& container);

    cyan::Arguments calleeArgs(token::Container& container);

    cyan::Expression identifier(token::Container& container);
}

#endif //BP_PARSER_HPP
