#include <codegen.hpp>
#include <stdexcept>

std::string Codegen::generate(Program& program) {
  std::string output;

  output += "global main\n";
  output += "section .text\n";
  output += "main:\n";

  for (const auto& stmt : program.statements) {
    output += generate_statement(*stmt);
  }

  return output;
}

std::string Codegen::generate_statement(Statement& stmt) {
  if (auto ret = dynamic_cast<ReturnStatement*>(&stmt)) {
    return generate_return(*ret);
  }

  throw std::runtime_error("Unknown statement type");
}

std::string Codegen::generate_expression(Expression& expr) {
  if (auto lit = dynamic_cast<IntegerLiteral*>(&expr)) {
    return "    mov eax, " + std::to_string(lit->value) + "\n";
  }

  throw std::runtime_error("Unknown expression type");
}

std::string Codegen::generate_return(ReturnStatement& stmt) {
  std::string output;

  output += generate_expression(*stmt.expression);
  output += "    ret\n";

  return output;
}
