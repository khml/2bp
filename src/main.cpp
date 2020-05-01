#include <iostream>
#include <string>

#include <cyan/cyan.hpp>

#include "Tokenizer.hpp"
#include "FileTokenizer.hpp"
#include "MacroLogger.hpp"

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
    }
}

void read_file_and_print(const string& filename)
{
    STD_ERR_LOG("filename:" << filename);

    token::FileTokenizer tokenizer(filename);
    auto tokens = tokenizer.tokenize();
    token::printTokens(tokens);
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

    cyan::Module module("main");
    auto& builder = cyan::Builder::instance();

    cyan::Function mainFunc("main", cyan::types::intType());
    module << mainFunc;

    builder.dump(module);
    builder.build("sample");

    return 0;
}