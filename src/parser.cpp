#include <cstdlib>
#include <memory>
#include <parser.hpp>

#include "ast.hpp"
#include "token.hpp"

const Token& Parser::peek() {
  if (position >= tokens.size()) {
    return tokens.back();
  }

  return tokens[position];
}

void Parser::advance() {
  if (position < tokens.size()) {
    position++;
  }
}

void Parser::consume(TokenType expected_type) {
  const Token& tok = peek();

  if (tok.type != expected_type) {
    std::string message = std::format(
        "<compile error>: Unexpected token \"{}\" provided at: Line: {}, Col: "
        "{}",
        tok.value.value_or(""), tok.location.line, tok.location.col);
    exit(EXIT_FAILURE);
  }
  advance();
}

std::unique_ptr<Expression> Parser::parseExpression() {
  const Token& tok = peek();

  switch (tok.type) {
    case TokenType::NUMBER:
      advance();
      return std::make_unique<IntegerLiteral>(std::stoi(tok.value.value()));
    case TokenType::IDENTIFIER:
      advance();
      return std::make_unique<Identifier>(tok.value.value());
    default:
      std::string message = std::format(
          "<compile error>: Unexpected token \"{}\" provided at: Line: {}, "
          "Col: "
          "{}",
          tok.value.value_or(""), tok.location.line, tok.location.col);
      exit(EXIT_FAILURE);
  }
}

std::unique_ptr<ReturnStatement> Parser::parseReturn() {
  consume(TokenType::RETURN);
  auto expr = parseExpression();
  consume(TokenType::SEMICOLON);
  return std::make_unique<ReturnStatement>(std::move(expr));
}

std::unique_ptr<Program> Parser::parse() {
  auto program = std::make_unique<Program>();
  while (peek().type != TokenType::END_OF_FILE) {
    std::unique_ptr<Statement> stmt;

    switch (peek().type) {
      case TokenType::RETURN: {
        stmt = parseReturn();
        break;
      }
      case TokenType::SEMICOLON:
        break;
      default:
        const Token& tok = peek();
        std::string message = std::format(
            "<compile error>: Unexpected token \"{}\" provided at: Line: {}, "
            "Col: "
            "{}",
            tok.value.value_or(""), tok.location.line, tok.location.col);
        exit(EXIT_FAILURE);
    }

    program->statements.push_back(std::move(stmt));
  }

  return program;
}