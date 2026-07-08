#pragma once

#include <string>
#include <token.hpp>
#include <vector>

class Lexer {
 public:
  int cursor;
  char character;
  std::string input;
  int line;
  int col;

  Lexer(std::string input);
  std::vector<Token> tokenize();

 private:
  void remove_whitespace();
  void read_char();
  std::string get_identifier();
  bool is_keyword(std::string);
  TokenType get_keyword_type(std::string);
  std::string get_number();
  Token next_token();
};
