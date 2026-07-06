#pragma once

#include <optional>
#include <string>
#include <unordered_map>

enum class TokenType : int
{
    // Special Tokens
    ILLEGAL,
    END_OF_FILE,

    // General
    IDENTIFIER,
    NUMBER,

    // Keywords
    FUNCTION,
    IF,
    RETURN,
    PRINT,
    LET,
    INT,

    // Punctuation
    ASSIGN,
    PLUS,
    MINUS,
    COMMA,
    SEMICOLON,
    COLON,
    LPAREN,
    RPAREN,
    LCURLY,
    RCURLY,
    QUOTES,
    DQUOTES
};

inline std::unordered_map<std::string, TokenType> keywords = {
    {"function", TokenType::FUNCTION}, {"if", TokenType::IF},
    {"let", TokenType::LET},           {"println", TokenType::PRINT},
    {"return", TokenType::RETURN},     {"int", TokenType::INT}};

class Token
{
public:
    std::optional<std::string> value;
    TokenType type;

    Token(TokenType type, std::optional<std::string> value);
    std::string to_str();

private:
    std::string token_type_to_str();
};
