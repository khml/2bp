//
// Created by KHML on 2020/04/07.
//

#ifndef BLUEPRINT_FILETOKENIZER_HPP
#define BLUEPRINT_FILETOKENIZER_HPP

#include "tokenizer.hpp"

namespace token
{
    class file_tokenizer : protected Tokenizer
    {
    public:
        explicit file_tokenizer(const std::string& filename);

        ~file_tokenizer() override;

        std::vector<Token> tokenize();

    protected:
        uint16_t row{};

        Token makeToken(token::kind::Kind kindVal, const std::string& value, token::type::Type type) override;

        Token makeToken(token::kind::Kind kindVal, const std::string& value) override;

        const std::string filename;

        std::vector<std::string> lines;
    };
}

#endif //BLUEPRINT_FILETOKENIZER_HPP
