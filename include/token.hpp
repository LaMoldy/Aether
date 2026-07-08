#pragma once

#include <optional>
#include <string>
#include <unordered_map>

enum class TokenType : int {
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

inline std::unordered_map<char, TokenType> token_types = {
    {'{', TokenType::LCURLY},      {'}', TokenType::RCURLY},
    {'(', TokenType::LPAREN},      {')', TokenType::RPAREN},
    {'=', TokenType::ASSIGN},      {'+', TokenType::PLUS},
    {'-', TokenType::MINUS},       {';', TokenType::SEMICOLON},
    {':', TokenType::COLON},       {',', TokenType::COMMA},
    {'"', TokenType::DQUOTES},     {'\'', TokenType::QUOTES},
    {'\0', TokenType::END_OF_FILE}};


class SourceLocation {
 public:
  std::string line;
  std::string col;

  SourceLocation(std::string line, std::string col);
};

class Token {
 public:
  std::optional<std::string> value;
  TokenType type;
  SourceLocation location;

  Token(TokenType type, SourceLocation location, std::optional<std::string> value);
  std::string to_str();

 private:
  std::string token_type_to_str() const;
  std::string location_to_str() const;
};
