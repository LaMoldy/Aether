#include <ast.hpp>
#include <ostream>

void Program::generate(std::ostream& out) {
  CodegenContext ctx;
  out << "global main\n";
  out << "section .text\n";
  out << "main:\n";

  for (const auto& stmt : statements) {
    stmt->generate(out, ctx);
  }

  out << "    mov edi, eax\n";
  out << "    mov eax, 60\n";
  out << "    syscall\n";
}

void IntegerLiteral::generate(std::ostream& out, CodegenContext& ctx) const {
  out << "    mov eax, " << value << "\n";
}

void Identifier::generate(std::ostream& out, CodegenContext& ctx) const {
  int offset = ctx.variables.at(value);

  out << "    mov eax, [rbp" << offset << "]\n";
}

void ReturnStatement::generate(std::ostream& out, CodegenContext& ctx) const {
  expression->generate(out, ctx);
  out << "    ret\n";
}