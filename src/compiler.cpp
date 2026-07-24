#include <compiler.hpp>
#include <fstream>
#include <iostream>
#include <lexer.hpp>
#include <sstream>

#include "codegen.hpp"
#include "parser.hpp"

void Compiler::print_usage() {
  std::cout << "Usage: aether <source file>.ae" << std::endl;
}

bool Compiler::is_valid_file_name() {
  const int REQUIRED_LENGTH = 4;
  return source_file.length() >= REQUIRED_LENGTH;
}

bool Compiler::is_valid_file_type() {
  const std::string REQUIRED_EXTENSION = ".ae";
  return source_file.ends_with(REQUIRED_EXTENSION);
}

std::string Compiler::get_file_data() {
  std::ifstream file(source_file);

  if (!file.is_open()) {
    std::cout << "<compiler error>: Failed to read the source file provided, "
                 "please try again"
              << std::endl;
    exit(EXIT_FAILURE);
  }

  std::stringstream buffer;
  buffer << file.rdbuf();

  return buffer.str();
}

void Compiler::validate() {
  if (!is_valid_file_name() || !is_valid_file_type()) {
    std::cout << "<compiler error>: Invalid file provided to the compiler"
              << std::endl;
    print_usage();
    exit(EXIT_FAILURE);
  }
}

void Compiler::tokenize() {
  std::string data = get_file_data();
  std::cout << "Data: " << std::endl << data << std::endl;
  Lexer lexer(data);
  tokens = lexer.tokenize();

  for (Token tok : tokens) {
    std::cout << tok.to_string() << std::endl;
  }
}

void Compiler::parse() {
  Parser parser = Parser(tokens);
  program = parser.parse();
}

void Compiler::generate() {
  Codegen codegen;
  std::string code = codegen.generate(*program);
  std::ofstream file("build/out.asm");
  file << code;
  file.close();
}

void Compiler::create_exe() {
  system("nasm -f win64 build/out.asm -o build/out.obj");
  system("gcc build/out.obj -o build/main.exe -mconsole");
  remove("./build/out.asm");
  remove("./build/out.obj");
}

void Compiler::run() {
  validate();
  tokenize();
  parse();
  generate();
  create_exe();
}
