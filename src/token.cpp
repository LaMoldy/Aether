#include <format>
#include <map>
#include <optional>
#include <token.hpp>

Token::Token(TokenType type, SourceLocation location,
             std::optional<std::string> value = std::nullopt)
    : type(type), location(location), value(value) {
  this->type = type;
  this->location = location;
  if (value.has_value()) {
    this->value = value;
  }
}

SourceLocation::SourceLocation(std::string line, std::string col)
    : line(line), col(col) {}

std::string Token::to_str() {
  std::string type = token_type_to_str();
  std::string value = this->value.value_or("N/A");
  std::string location = location_to_str();
  return std::format("Token Type: {}, Value: {}, Location: {}", type, value,
                     location);
}

std::string Token::token_type_to_str() const {
  std::map<TokenType, std::string> token_types = {
      // Special Tokens
      {TokenType::ILLEGAL, "Illegal"},
      {TokenType::END_OF_FILE, "EOF"},

      // General
      {TokenType::IDENTIFIER, "Identifier"},
      {TokenType::NUMBER, "Number"},

      // Keywords
      {TokenType::FUNCTION, "Function Keyword"},
      {TokenType::IF, "If Keyword"},
      {TokenType::LET, "Let keyword"},
      {TokenType::PRINT, "Print keyword"},
      {TokenType::RETURN, "Return keyword"},
      {TokenType::INT, "Int Keyword"},

      // Punctuation
      {TokenType::ASSIGN, "Assign"},
      {TokenType::PLUS, "Plus"},
      {TokenType::MINUS, "Minus"},
      {TokenType::COMMA, "Comma"},
      {TokenType::SEMICOLON, "Semi Colon"},
      {TokenType::COLON, "Colon"},
      {TokenType::LPAREN, "Left Parenthesis"},
      {TokenType::RPAREN, "Right Parenthesis"},
      {TokenType::LCURLY, "Left Curly"},
      {TokenType::RCURLY, "Right Curly"},
      {TokenType::QUOTES, "Quotes"},
      {TokenType::DQUOTES, "Double Quotes"}};
  return token_types[type];
}

std::string Token::location_to_str() const {
  std::string line_num = location.line;
  std::string char_col = location.col;
  return std::format("Line: {}, Column: {}", line_num, char_col);
}
