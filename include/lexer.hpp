#pragma once

#include <token.hpp>
#include <vector>

inline std::unordered_map<std::string, TokenType> keywords = {
    {"ret", TokenType::RETURN}};

class Lexer {
 public:
  std::string input;
  int cursor;
  char character;
  int line;
  int col;

  Lexer(std::string input);
  std::vector<Token> tokenize();

 private:
  bool is_keyword(std::string value);
  TokenType get_keyword_type(std::string value);
  void read_char();
  void remove_whitespace();
  std::string get_identifier();
  std::string get_number();
  Token get_next_token();
};
