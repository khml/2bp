//
// Created by KHML on 2020/01/08.
//

#include <iostream>
#include <utility>

#include "MacroLogger.hpp"
#include "FileReader.hpp"
#include "Tokenizer.hpp"

namespace token
{
    void printTokens(const std::vector<Token>& tokens)
    {
        for (auto token : tokens)
            token.print();
    }

    Tokenizer::Tokenizer()
    = default;

    Tokenizer::~Tokenizer()
    = default;

    Token Tokenizer::makeToken(token::kind::Kind kindVal, const std::string& value, token::type::Type type)
    {
        return Token(kindVal, value, type);
    }

    Token Tokenizer::makeToken(token::kind::Kind kindVal, const std::string& value)
    {
        return Token(kindVal, value);
    }

    void Tokenizer::pushToken(token::kind::Kind kindVal, const std::string& value, token::type::Type type)
    {
        tokens.emplace_back(makeToken(kindVal, value, type));
    }

    void Tokenizer::pushToken(token::kind::Kind kindVal, const std::string& value)
    {
        tokens.emplace_back(makeToken(kindVal, value));
    }

    void Tokenizer::readMultiCharOperator(token::kind::Kind kind, const std::string& ch, const int size)
    {
        if (indicator + size - 1 >= line.size())
        {
            // end of line
            pushToken(kind, ch);
            return;
        }

        auto multiCharOp = line.substr(indicator, size);
        auto kindVal = token::kind::toTokenKind(multiCharOp);

        if (kindVal == token::kind::IDENTIFIER)
        {
            // rollback
            multiCharOp = ch;
            kindVal = kind;
        }
        else
            indicator++;

        pushToken(kindVal, multiCharOp);
    }

    void Tokenizer::readString(const std::string& mark)
    {
        int start = indicator++;
        for (; indicator < line.size(); indicator++)
        {
            auto ch = line.substr(indicator, 1);
            if (ch == "\\")
            {
                indicator++;
                continue;
            }
            if (ch == mark)
            {
                auto str = line.substr(start + 1, (indicator - start - 1));
                pushToken(token::kind::IDENTIFIER, str, token::type::STRING);
                return;
            }
        }
        STD_ERR_LOG("expected : " << mark << " but not given.");
        exit(1);
    }

    void Tokenizer::readIdentifier()
    {
        int start = indicator++;
        token::kind::Kind kind;

        for (; indicator < line.size(); indicator++)
        {
            kind = token::kind::toTokenKind(line.substr(indicator, 1));
            if (kind != token::kind::IDENTIFIER)
            {
                --indicator;
                break;
            }
        }

        auto identifier = line.substr(start, (indicator - start + 1));
        kind = token::kind::toTokenKind(identifier);
        pushToken(kind, identifier);
    }

    void Tokenizer::readNumber()
    {
        int start = indicator;
        bool isDotAppeared = false;
        std::string ch;
        for (; indicator < line.size(); indicator++)
        {
            ch = line.substr(indicator, 1);
            if (ch == ".")
            {
                // allow dot only once
                if (isDotAppeared)
                    break;
                isDotAppeared = true;
            }
            else if (token::type::isDigit(ch))
                continue;
            else if (ch == "f")
            {
                indicator++;
                break;
            }
            else
                break;
        }
        ch = line.substr(start, indicator - start);
        pushToken(token::kind::IDENTIFIER, ch);
        --indicator;
    }

    std::vector<Token> Tokenizer::tokenize(const std::string& _line)
    {
        tokens = std::vector<Token>();
        line = _line;

        std::string ch;
        token::kind::Kind kind;

        LOG_DEBUG(line);
        for (indicator = 0; indicator < line.size(); indicator++)
        {
            ch = line.substr(indicator, 1);
            kind = token::kind::toTokenKind(ch);
            LOG_DEBUG("idx: " << indicator << ", kind: " << token::kind::fromTokenKind(kind) << ", ch: " << ch);
            switch (kind)
            {
                /*
                 * if token is identifier, stored the one char.
                 * if token is whitespace, tokenize stored strings.
                 * else, tokenize stored strings, and put the token.
                 */
                case token::kind::IDENTIFIER:
                    if (token::type::isDigit(ch))
                        readNumber();
                    else
                        readIdentifier();
                    break;
                case token::kind::WHITESPACE:
                    break;
                case token::kind::ADD:
                case token::kind::SUB:
                case token::kind::ASTERISK:
                case token::kind::SLASH:
                case token::kind::EQUAL:
                case token::kind::GRATER_THAN:
                case token::kind::LESSER_THAN:
                case token::kind::AMPERSAND:
                case token::kind::PIPE:
                    readMultiCharOperator(kind, ch, 2);
                    break;
                case token::kind::APOSTROPHE:
                case token::kind::QUOTATION:
                    readString(ch);
                    break;
                default:
                    pushToken(kind, ch);
                    break;
            }
            LOG_DEBUG("idx: " << indicator << ", kind: " << token::kind::fromTokenKind(kind) << ", ch: " << ch);
        }
        return std::move(tokens);
    }
}
