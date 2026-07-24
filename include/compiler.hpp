#pragma once

#include <memory>
#include <string>
#include <token.hpp>
#include <vector>

#include "parser.hpp"

class Compiler {
 public:
  const std::string source_file;
  std::vector<Token> tokens;
  std::unique_ptr<Program> program;

  Compiler(const std::string source_file)
      : source_file(std::move(source_file)) {};

  static void print_usage();
  void validate();
  void tokenize();
  void parse();
  void generate();
  void create_exe();
  void run();

 private:
  bool is_valid_file_type();
  bool is_valid_file_name();
  std::string get_file_data();
  void create_asm_file(std::string src);
};
