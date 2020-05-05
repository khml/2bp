//
// Created by KHML on 2020/04/07.
//

#include <algorithm>
#include <utility>

#include "file_reader.hpp"
#include "tokenizer.hpp"
#include "file_tokenizer.hpp"

namespace token
{
    file_tokenizer::file_tokenizer(const std::string& filename) :filename(filename), lines(io::readFile(filename))
    {}

    file_tokenizer::~file_tokenizer()
    = default;

    std::vector<Token> file_tokenizer::tokenize()
    {
        row = 0;
        std::vector<Token> allTokens;

        for (auto& line : lines)
        {
            std::vector<Token> tokens = Tokenizer::tokenize(line);
            row++;

            if(tokens.empty())
                continue;

            switch (tokens.front().kind)
            {
                case token::kind::CLASS:
                case token::kind::STRUCT:
                case token::kind::FUNCTION:
                case token::kind::IF:
                case token::kind::ELIF:
                case token::kind::ELSE:
                case token::kind::FOR:
                case token::kind::SWITCH:
                case token::kind::CASE:
                    break;
                default:
                    switch (tokens.back().kind)
                    {
                        case token::kind::IDENTIFIER:
                        case token::kind::INCREMENTAL:
                        case token::kind::DECREMENTAL:
                        case token::kind::PARENTHESISE_RIGHT:
                            tokens.emplace_back(token::Token(token::kind::SEMICOLON, ";"));
                            break;
                        default:
                            break;
                    }
            }

            allTokens.reserve(allTokens.size() + tokens.size());
            std::move(tokens.begin(), tokens.end(), std::back_inserter(allTokens));

        }
        return std::move(allTokens);
    }

    Token file_tokenizer::makeToken(token::kind::Kind kindVal, const std::string& value, token::type::Type type)
    {
        return Token(kindVal, value, type, filename, row);
    }

    Token file_tokenizer::makeToken(token::kind::Kind kindVal, const std::string& value)
    {
        return Token(kindVal, value, filename, row);
    }
}