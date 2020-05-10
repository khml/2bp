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
    FileTokenizer::FileTokenizer(const std::string& filename) :filename(filename), lines(io::readFile(filename))
    {}

    FileTokenizer::~FileTokenizer()
    = default;

    std::vector<Token> FileTokenizer::tokenize()
    {
        row = 0;
        std::vector<Token> allTokens;

        auto tokenizedLineList = tokenizeFile();

        for (auto& tokens : tokenizedLineList)
        {
            if (tokens.empty())
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
                case token::kind::WHILE:
                case token::kind::SWITCH:
                case token::kind::CASE:
                    break;
                default:
                    switch (tokens.back().kind)
                    {
                        case token::kind::IDENTIFIER:
                        case token::kind::INCREMENTAL:
                        case token::kind::DECREMENTAL:
                        case token::kind::PARENTHESIS_RIGHT:
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

    Token FileTokenizer::makeToken(token::kind::Kind kindVal, const std::string& value, token::type::Type type)
    {
        return Token(kindVal, value, type, filename, row);
    }

    Token FileTokenizer::makeToken(token::kind::Kind kindVal, const std::string& value)
    {
        return Token(kindVal, value, filename, row);
    }

    std::vector<std::vector<Token>> FileTokenizer::tokenizeFile()
    {
        row = 0;
        std::vector<std::vector<Token>> tokenizedLines;

        std::vector<Token> braceLeft({Token(kind::BRACE_LEFT, "{")});
        std::vector<Token> braceRight({Token(kind::BRACE_RIGHT, "}")});

        size_t preIndent = 0;
        size_t postIndent = 0;
        size_t depth = 0;
        for (auto& line : lines)
        {
            auto tokenList = Tokenizer::tokenize(line);
            row++;
            postIndent = tokenList.back().value.size();
            tokenList.pop_back();

            if (tokenList.empty())
                continue;

            if (postIndent < preIndent)
            {
                tokenizedLines.emplace_back(braceRight);
                depth--;
            }

            if (postIndent == 0)
            {
                while (depth > 0)
                {
                    tokenizedLines.emplace_back(braceRight);
                    depth--;
                }
            }

            if (postIndent > preIndent)
            {
                tokenizedLines.emplace_back(braceLeft);
                depth++;
            }

            tokenizedLines.emplace_back(tokenList);

            preIndent = postIndent;
        }

        while (depth > 0)
        {
            tokenizedLines.emplace_back(braceRight);
            depth--;
        }

        return tokenizedLines;
    }
}