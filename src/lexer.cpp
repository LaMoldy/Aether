#include <cctype>
#include <lexer.hpp>
#include <token.hpp>

Lexer::Lexer(std::string input) {
  this->input = input;
  cursor = 1;
  character = input.empty() ? '\0' : input[0];
  line = 1;
  col = 1;
}

bool Lexer::is_keyword(std::string input) { return keywords.contains(input); }
TokenType Lexer::get_keyword_type(std::string value) { return keywords[value]; }

void Lexer::remove_whitespace() {
  while (std::isspace(character)) {
    if (character == '\n' || character == '\r') {
      line++;
      col = 1;
    }
    read_char();
  }
}

std::string Lexer::get_identifier() {
  std::string result = "";
  while (std::isalpha(character) || character == '_') {
    result += character;
    read_char();
  }
  return result;
}

std::string Lexer::get_number() {
  std::string result = "";
  while (std::isdigit(character)) {
    result += character;
    read_char();
  }
  return result;
}

void Lexer::read_char() {
  if (cursor >= input.size()) {
    character = 0;
    col = 1;
  } else {
    character = input[cursor];
  }
  cursor++;
}

Token Lexer::get_next_token() {
  remove_whitespace();

  std::string value = "";
  TokenType type;

  if ((character >= 'a' && character <= 'z') ||
      (character >= 'A' && character <= 'Z')) {
    value = get_identifier();
    if (is_keyword(value)) {
      type = get_keyword_type(value);
    } else {
      type = TokenType::IDENTIFIER;
    }
    col = cursor - value.length();
    cursor--;
  } else if (character >= '0' && character <= '9') {
    value = get_number();
    type = TokenType::NUMBER;
    col = cursor - value.length();
    cursor--;
  } else {
    if (!token_types.contains(character)) {
      type = TokenType::END_OF_FILE;
    } else {
      type = token_types[character];
    }
    col = cursor + 1;
  }

  if (value == "") {
    value += character;
  }
  read_char();
  return Token(value, type, line, col);
}

std::vector<Token> Lexer::tokenize() {
  std::vector<Token> tokens = std::vector<Token>();
  while (cursor <= input.size()) {
    Token tok = get_next_token();
    tokens.push_back(tok);
  }

  return tokens;
}
