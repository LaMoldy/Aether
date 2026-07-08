#pragma once

#include <ast.hpp>
#include <memory>
#include <token.hpp>
#include <vector>

class Parser {
 public:
  Parser(const std::vector<Token>& tokens) : tokens(tokens), position(0) {}
  std::unique_ptr<Program> parse();

 private:
  std::vector<Token> tokens;
  size_t position;

  const Token& peek();
  const Token& consume(TokenType expected);
  const Token& advance();

  std::unique_ptr<Expression> parseExpression();
  std::unique_ptr<ReturnStatement> parseReturnStatement();
  // std::unique_ptr<LetStatement> parseLetStatement();
};
