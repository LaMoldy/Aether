#pragma once

#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

struct CodegenContext {
  std::unordered_map<std::string, int> variables;
};

class Node {
 public:
  virtual ~Node() = default;
  virtual void generate(std::ostream& out, CodegenContext& ctx) const = 0;
};

class Statement : public Node {};
class Expression : public Node {};

struct Program {
  std::vector<std::unique_ptr<Statement>> statements;
  void generate(std::ostream& out);
};

struct IntegerLiteral : Expression {
  int value;

  IntegerLiteral(int value) : value(value) {}
  void generate(std::ostream& out, CodegenContext& ctx) const override;
};

struct Identifier : Expression {
  std::string value;

  Identifier(std::string value) : value(value) {}
  virtual void generate(std::ostream& out, CodegenContext& ctx) const override;
};

struct Type : Expression {
  std::string type;

  Type(std::string type) : type(type) {}
  virtual void generate(std::ostream& out, CodegenContext& ctx) const override;
};

struct ReturnStatement : Statement {
  std::unique_ptr<Expression> expression;
  ReturnStatement(std::unique_ptr<Expression> expr)
      : expression(std::move(expr)) {}

  void generate(std::ostream& out, CodegenContext& ctx) const override;
};

// struct LetStatement : Statement {
//   std::unique_ptr<Expression> expression;
//   LetStatement(std::unique_ptr<Expression> expression)
//       : expression(std::move(expression)) {}

//   void generate(std::ostream& out, CodegenContext& ctx) const override;
// };
