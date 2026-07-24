#pragma once

#include <memory>
#include <token.hpp>
#include <vector>

class Node {
 public:
  virtual ~Node() = default;
};

class Expression : Node {};
class Statement : Node {};

class Program {
 public:
  std::vector<std::unique_ptr<Statement>> statements;
};

class ReturnStatement : public Statement {
 public:
  std::unique_ptr<Expression> expression;
  ReturnStatement(std::unique_ptr<Expression> expression)
      : expression(std::move(expression)) {}
};

class IntegerLiteral : public Expression {
 public:
  int value;
  IntegerLiteral(int value) : value(value) {}
};

class Parser {
 public:
  Parser(std::vector<Token>& tokens);
  std::unique_ptr<Program> parse();

 private:
  std::vector<Token> tokens;
  int position;

  Token& peek();
  void consume(TokenType expected);
  void advance();
  std::unique_ptr<Expression> parse_expression();
  std::unique_ptr<ReturnStatement> parse_return();
};
