#include <format>
#include <token.hpp>
#include <unordered_map>

Token::Token(std::string value, TokenType type, int line, int col)
    : type(type), line(line), col(col), value(value) {
  this->type = type;
  this->value = value;
  this->line = line;
  this->col = col;
}

std::string Token::token_type_to_string(TokenType type) { return types[type]; }

std::string Token::to_string() {
  return std::format("Token Type: {}, Value: {}, Line: {}, Column: {}",
                     Token::token_type_to_string(type), value, line, col);
}
