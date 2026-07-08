#include <ast.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <parser.hpp>
#include <string>
#include <token.hpp>

const Token& Parser::peek() {
  if (position >= tokens.size()) {
    return tokens.back();
  }

  return tokens[position];
}

const Token& Parser::advance() {
  if (position < tokens.size()) {
    position++;
  }

  return peek();
}

const Token& Parser::consume(TokenType expected) {
  const Token& token = peek();

  if (token.type != expected) {
    std::cerr << "Expected token type " << (int)expected << " but got "
              << (int)token.type << " (" << token.value.value() << ")\n";

    std::exit(EXIT_FAILURE);
  }

  return advance();
}

std::unique_ptr<Program> Parser::parse() {
  auto program = std::make_unique<Program>();

  while (peek().type != TokenType::END_OF_FILE) {
    std::unique_ptr<Statement> stmt;

    switch (peek().type) {
      case TokenType::RETURN:
        stmt = parseReturnStatement();
        break;
      case TokenType::SEMICOLON:
        break;
      default:
        Token next_tok = peek();
        std::cerr << "Unexpected token: " << next_tok.to_str() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    program->statements.push_back(std::move(stmt));
  }
  return program;
}

std::unique_ptr<Expression> Parser::parseExpression() {
  const Token& token = peek();
  switch (token.type) {
    case TokenType::NUMBER: {
      advance();
      return std::make_unique<IntegerLiteral>(std::stoi(token.value.value()));
    }

    case TokenType::IDENTIFIER: {
      advance();

      return std::make_unique<Identifier>(token.value.value());
    }

    default: {
      std::cerr << "Unexpected token in expression: " << token.value.value()
                << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }
}

std::unique_ptr<ReturnStatement> Parser::parseReturnStatement() {
  consume(TokenType::RETURN);
  auto expr = parseExpression();
  consume(TokenType::SEMICOLON);
  return std::make_unique<ReturnStatement>(std::move(expr));
}

// std::unique_ptr<LetStatement> Parser::parseLetStatement() {
//   consume(TokenType::LET);
//   consume(TokenType::COLON);
//   auto expr = parseExpression();
//   consume(TokenType::SEMICOLON);
//   return std::make_unique<LetStatement>(std::move(expr));
// }
