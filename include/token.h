#pragma once

#include <optional>
#include <string>

enum class TokenType : int {
  ILLEGAL,
  END_OF_FILE,
  IDENTIFIER,
  NUMBER,
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

class Token {
 public:
  std::optional<std::string> value;
  TokenType type;

  Token(TokenType type, std::optional<std::string> value);
  std::string to_str();

 private:
  std::string token_type_to_str();
};
