#include <cctype>
#include <lexer.hpp>
#include <token.hpp>

Lexer::Lexer(std::string input) {
  cursor = 0;
  character = input.empty() ? '\0' : input[0];
  this->input = input;
  line = 1;
  col = 1;
}

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

bool Lexer::is_keyword(std::string value) { return keywords.contains(value); }

TokenType Lexer::get_keyword_type(std::string value) { return keywords[value]; }

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
    col--;
  } else {
    character = input[cursor];
  }
  col++;
  cursor++;
}

Token Lexer::next_token() {
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

    cursor--;
  } else if (character >= '0' && character <= '9') {
    value = get_number();
    type = TokenType::NUMBER;
    cursor--;
  } else {
    if (!token_types.contains(character)) {
      type = TokenType::ILLEGAL;
    } else {
      type = token_types[character];
    }
  }

  if (value == "") {
    value += character;
  }

  read_char();
  SourceLocation sourceLocation(std::to_string(line), std::to_string(col));
  return Token(type, sourceLocation, value);
}

std::vector<Token> Lexer::tokenize() {
  std::vector<Token> tokens = std::vector<Token>();
  read_char();
  while (cursor <= input.size()) {
    Token token = next_token();
    tokens.push_back(token);
  }
  return tokens;
}
