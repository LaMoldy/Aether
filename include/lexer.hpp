#pragma once

#include <string>
#include <token.hpp>
#include <vector>

class Lexer
{
public:
    int cursor;
    char character;
    std::string input;

    Lexer(std::string input);
    std::vector<Token> tokenize();

private:
    void remove_whitespace();
    void read_char();
    std::string get_identifier();
    std::string get_number();
    Token next_token();
};
