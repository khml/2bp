//
// Created by KHML on 2020/04/07.
//

#ifndef BLUEPRINT_FILETOKENIZER_HPP
#define BLUEPRINT_FILETOKENIZER_HPP

#include "Tokenizer.hpp"

namespace token
{
    class FileTokenizer : protected Tokenizer
    {
    public:
        explicit FileTokenizer(const std::string& filename);

        ~FileTokenizer() override;

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
