#include <cstdlib>
#include <iostream>
#include <memory>
#include <parser.hpp>

#include "token.hpp"

Parser::Parser(std::vector<Token>& tokens) : tokens(std::move(tokens)) {
  position = 0;
}

std::unique_ptr<Program> Parser::parse() {
  auto program = std::make_unique<Program>();

  while (peek().type != TokenType::END_OF_FILE) {
    std::unique_ptr<Statement> stmt;
    switch (peek().type) {
      case TokenType::RETURN: {
        stmt = parse_return();
        break;
      }
      default:
        const Token& tok = peek();
        std::cout << "<parse error>: Invalid token provided at Line: "
                  << tok.line << " Col: " << tok.col << std::endl;
        exit(EXIT_FAILURE);
    }

    program->statements.push_back(std::move(stmt));
  }

  return program;
}

Token& Parser::peek() {
  if (position >= tokens.size()) return tokens.back();
  return tokens[position];
}

void Parser::consume(TokenType type) {
  Token& tok = peek();

  if (tok.type != type) {
    std::cout << "<compiler error>: Unexpected token reached: "
              << tok.to_string() << std::endl;
    exit(EXIT_FAILURE);
  }

  advance();
}

void Parser::advance() {
  if (position < tokens.size()) {
    position++;
  }
}

std::unique_ptr<Expression> Parser::parse_expression() {
  Token& tok = peek();
  switch (tok.type) {
    case TokenType::NUMBER:
      advance();
      return std::make_unique<IntegerLiteral>(std::stoi(tok.value));
    default:
      exit(EXIT_FAILURE);
  }
}

std::unique_ptr<ReturnStatement> Parser::parse_return() {
  consume(TokenType::RETURN);
  auto expr = parse_expression();
  return std::make_unique<ReturnStatement>(std::move(expr));
}
