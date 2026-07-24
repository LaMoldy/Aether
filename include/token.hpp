#pragma once

#include <string>
#include <unordered_map>

enum class TokenType : int {
  // GENERAL
  END_OF_FILE,
  IDENTIFIER,
  NUMBER,

  // KEYWORDS
  RETURN
};

inline std::unordered_map<TokenType, std::string> types = {
    {TokenType::END_OF_FILE, "EOF"},
    {TokenType::IDENTIFIER, "Identifier"},
    {TokenType::NUMBER, "Number"},
    {TokenType::RETURN, "Return"}};

inline std::unordered_map<char, TokenType> token_types = {
    {'\0', TokenType::END_OF_FILE}};

class Token {
 public:
  std::string value;
  TokenType type;
  int line;
  int col;

  Token(std::string value, TokenType type, int line, int col);
  std::string to_string();

 private:
  static std::string token_type_to_string(TokenType type);
};
