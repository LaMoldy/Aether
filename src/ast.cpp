#include <ast.hpp>
#include <ostream>

int CodegenContext::add_string(const std::string& value) {
  for (size_t i = 0; i < strings.size(); i++) {
    if (strings[i] == value) {
      return i;
    }
  }

  strings.push_back(value);
  return strings.size() - 1;
}

void Program::generate(std::ostream& out) {
  CodegenContext ctx;

  // First pass: collect strings
  for (const auto& stmt : statements) {
    stmt->collect_strings(ctx);
  }

  out << "global main\n";

  out << "section .data\n";
  for (size_t i = 0; i < ctx.strings.size(); i++) {
    out << "str" << i << " db \"" << ctx.strings[i] << "\", 10\n";
  }

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

void PrintStatement::generate(std::ostream& out, CodegenContext& ctx) const {
  expression->collect_strings(ctx);
  expression->generate(out, ctx);

  out << "    mov rsi, rax\n";  // string address
  out << "    mov rax, 1\n";    // write syscall
  out << "    mov rdi, 1\n";    // stdout
  out << "    mov rdx, 13\n";   // string length
  out << "    syscall\n";
}

void StringLiteral::generate(std::ostream& out, CodegenContext& ctx) const {
  int id = ctx.add_string(value);

  out << "    lea rax, [rel str" << id << "]\n";
}

void StringLiteral::collect_strings(CodegenContext& ctx) const {
  ctx.add_string(value);
}

void LetStatement::generate(std::ostream& out, CodegenContext& ctx) const {}