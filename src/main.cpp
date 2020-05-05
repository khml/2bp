#include <iostream>
#include <string>

#include <cyan/cyan.hpp>

#include "container.hpp"
#include "tokenizer.hpp"
#include "file_tokenizer.hpp"
#include "macro_logger.hpp"
#include "parser.hpp"

using std::string;
using std::cerr;
using std::endl;
using std::cin;

void read_print_loop()
{
    string line;

    while (true)
    {
        cerr << "> ";
        getline(cin, line);

        if (line == "end")
            break;
        if (line.empty())
            continue;

        token::Tokenizer tokenizer;
        auto tokens = tokenizer.tokenize(line);
        token::printTokens(tokens);
        auto container = token::Container(tokens);
    }
}

void read_file_and_print(const string& filename)
{
    //STD_ERR_LOG("filename = " << filename);

    token::file_tokenizer tokenizer(filename);
    auto tokens = tokenizer.tokenize();
    //token::printTokens(tokens);
    auto container = token::Container(tokens);
    auto result = parser::statement(container);
    //STD_ERR_LOG("result = " << result());

    // create an executable file
    cyan::Module module("main");
    module.include2c("iostream");
    auto& builder = cyan::Builder::instance();

    cyan::Function mainFunc("main", cyan::types::intType());
    mainFunc << result;

    auto zero = cyan::Literal(0);
    mainFunc().createRetValue(zero);
    module << mainFunc;

    builder.dump(module);
    builder.build("a.out");
}

int main(int argc, char* argv[])
{
    if (argc == 1)
        read_print_loop();
    else
    {
        string filename = argv[1];
        read_file_and_print(filename);
    }

    return 0;
}