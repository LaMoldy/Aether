#pragma once

#include <parser.hpp>
#include <string>

class Codegen {
 public:
  Codegen() {}
  std::string generate(Program& program);

 private:
  std::string generate_expression(Expression& expr);
  std::string generate_statement(Statement& stmt);
  std::string generate_return(ReturnStatement& stmt);
};
