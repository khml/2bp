# -*- coding:utf-8 -*-

from collections import OrderedDict

HEADER_FILE_NAME = "../headers/TokenKind.hpp"
IMPL_FILE_NAME = "../src/TokenKind.cpp"
NAME_SPACE = "tokenKind"

TokenKind = OrderedDict([
    ('ADD', '+'),
    ('SUB', '-'),
    ('ASTERISK', '*'),
    ('SLASH', '/'),
    ('AT', '@'),
    ('EQUAL', '='),
    ('PARENTHESISE_RIGHT', ')'),
    ('PARENTHESIS_LEFT', '('),
    ('BRACKET_RIGHT', ']'),
    ('BRACKET_LEFT', '['),
    ('BRACE_RIGHT', '}'),
    ('BRACE_LEFT', '{'),
    ('DOT', '.'),
    ('COMMA', ','),
    ('COLON', ':'),
    ('SEMICOLON', ';'),
    ('INTERROGATION', '?'),
    ('GRATER_THAN', '>'),
    ('LESSER_THAN', '<'),
    ('APOSTROPHE', "\\'"),
    ('QUOTATION', '\\"'),
    ('AMPERSAND', '&'),
    ('PERCENT', '%'),
    ('DOLLAR', '$'),
    ('SHARP', '#'),
    ('PIPE', '|'),
    ('UNDER_BAR', '_'),
    ('BACKSLASH', '\\\\'),
    ('WHITESPACE', ' '),
    ('NEW_LINE', '\\n'),
    ("EQUIVALENCE", "=="),
    ("GRATER", ">="),
    ("LESSER", "<="),
    ("INCREMENTAL", "++"),
    ("DECREMENTAL", "--"),
    ("AND", "&&"),
    ("OR", "||"),
    ("COMMENT_START", "/*"),
    ("COMMENT_END", "*/"),
    ("ARROW", "->"),
    ("FAT_ARROW", "=>"),
    ('IDENTIFIER', ''),

    # keywords
    ("CLASS", 'class'),
    ("STRUCT", 'struct'),
    ("FUNCTION", 'fn'),

    # primitive types
    ('STRING', 'string'),
    ("INT", 'int'),
    ("FLOAT", 'float'),
    ("DOUBLE", 'double'),
    ("BOOL", 'bool'),
    ("VOID", 'void'),

    # control syntax
    ("RETURN", 'return'),
    ("IF", 'if'),
    ("ELSE", 'else'),
    ("ELIF", 'elif'),
    ("FOR", 'for'),
    ("WHILE", 'while'),
    ("SWITCH", 'switch'),
    ("CASE", 'case'),
])

SPECIAL_TYPES = ["IDENTIFIER"]


class Header:
    HEADER_TEMPLATE = """\
// This File is Auto Generated.
#ifndef BLUEPRINT_TOKEN_KIND_HPP
#define BLUEPRINT_TOKEN_KIND_HPP

#include <string>

namespace token
{{
    namespace kind
    {{
    {content}
        Kind toTokenKind(const std::string& val);
        
        Kind toTokenKind(const std::string&& val);
        
        std::string fromTokenKind(Kind val);
    }}
}}
#endif //BLUEPRINT_TOKEN_KIND_HPP
"""

    ENUM_TEMPLATE = """\
    enum Kind
        {{\
    {impl}
        LINE_START,
        }};
"""

    ITEM_FORMAT = "\n        {kind}, /* {value} */"
    ITEM_FORMAT_FOR_COMMENT_TOKEN = "\n        {kind}, // {value}"

    def __init__(self):
        header_content = self.HEADER_TEMPLATE.format(content=self._enum)
        with open(HEADER_FILE_NAME, "w") as f:
            f.write(header_content)

    @property
    def _enum(self):
        enum_impl = ""
        for kind_name, kind_value in TokenKind.items():
            if kind_name in ["COMMENT_START", "COMMENT_END"]:
                enum_impl += self.ITEM_FORMAT_FOR_COMMENT_TOKEN.format(kind=kind_name, value=kind_value)
            else:
                enum_impl += self.ITEM_FORMAT.format(kind=kind_name, value=kind_value)
        return self.ENUM_TEMPLATE.format(impl=enum_impl)


class Impl:
    IMPL_TEMPLATE = """\
// This File is Auto Generated.

#include <map>

#include "TokenKind.hpp"

namespace token
{{
    namespace kind
    {{
    {content}\
        Kind toTokenKind(const std::string&& val)
        {{
            return toTokenKind(val);
        }}
    }}
}}
"""

    SWITCH_FORMAT = """\
        {return_type} {name}({arg_type} val)
        {{
            switch (val)
            {{
                case LINE_START:
                    return "LINE_START";
{impl}
            }}
        }};

"""

    CASE_FORMAT = """\
                {case}:
                    return {value};
"""

    MAP_FORMAT = """\
    static std::map<std::string, Kind> toTokenKindMap()
        {{
            return std::map<std::string, Kind>{{
{impl}\
            }};
        }}

"""

    def __init__(self):
        impl_content = self._map + self._to_enum + self._to_str
        impl_content = self.IMPL_TEMPLATE.format(content=impl_content)
        with open(IMPL_FILE_NAME, "w") as f:
            f.write(impl_content)

    @property
    def _to_str(self):
        to_str_impl = ""
        for kind_name, kind_value in TokenKind.items():
            to_str_impl += self.CASE_FORMAT.format(case="case {}".format(kind_name), value='"{}"'.format(kind_name))
        to_str_impl += self.CASE_FORMAT.format(case="default", value='"{}"'.format("IDENTIFIER"))
        return self.SWITCH_FORMAT.format(return_type="std::string", arg_type="Kind", name="fromTokenKind",
                                         impl=to_str_impl)

    @property
    def _to_enum(self):
        return """\
        Kind toTokenKind(const std::string& val)
        {
            static std::map<std::string, Kind> dictionary = toTokenKindMap();
    
            auto iter = dictionary.find(val);
            if (iter != end(dictionary)) 
            {
                return iter->second;
            } 
            else 
            {
                return IDENTIFIER;
            }
        };

"""

    @property
    def _map(self):
        map_impl = ""
        item_format = "                {{\"{string}\", {kind}}},\n"
        for kind_name, kind_value in TokenKind.items():
            if kind_name in SPECIAL_TYPES:
                continue
            map_impl += item_format.format(string=kind_value, kind=kind_name)
        return self.MAP_FORMAT.format(impl=map_impl)


def main():
    Header()
    Impl()


if __name__ == '__main__':
    main()
