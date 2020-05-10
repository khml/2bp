//
// Created by KHML on 2020/04/07.
//

#ifndef BLUEPRINT_FILETOKENIZER_HPP
#define BLUEPRINT_FILETOKENIZER_HPP

#include "tokenizer.hpp"

namespace token
{
    class FileTokenizer : protected Tokenizer
    {
    public:
        explicit FileTokenizer(const std::string& filename);

        ~FileTokenizer() override;

        std::vector<Token> tokenize();

    protected:
        size_t row{};

        const std::string filename;

        std::vector<std::string> lines;

        Token makeToken(token::kind::Kind kindVal, const std::string& value, token::type::Type type) override;

        Token makeToken(token::kind::Kind kindVal, const std::string& value) override;

        std::vector<std::vector<Token>> tokenizeFile();
    };
}

#endif //BLUEPRINT_FILETOKENIZER_HPP
