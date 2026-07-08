#include <ast.hpp>
#include <compiler.hpp>
#include <cstdlib>
#include <errors.hpp>
#include <fstream>
#include <iostream>
#include <lexer.hpp>
#include <parser.hpp>
#include <sstream>
#include <token.hpp>
#include <validation.hpp>

void Compiler::init(int argc, char* argv[]) {
  ErrorType error = validate(argc, argv);
  if (error != ErrorType::NONE) {
    Error::print_error(error);
    std::exit(EXIT_FAILURE);
  }

  std::string file_path = Compiler::get_file_path(argv);
  std::string file_content;

  error = Compiler::read_file(file_path, &file_content);
  if (error != ErrorType::NONE) {
    Error::print_error(error);
    std::exit(EXIT_FAILURE);
  }

  Lexer lexer = Lexer(file_content);
  std::vector<Token> tokens = lexer.tokenize();

  for (Token token : tokens) {
    std::cout << token.to_str() << std::endl;
  }

  Parser parser = Parser(tokens);
  std::unique_ptr<Program> statements = parser.parse();

  Program program;
  std::ofstream file("build/out.asm");
  statements->generate(file);
  file.close();

  system("nasm -f win64 build/out.asm -o build/out.obj");
  system("gcc build/out.obj -o build/main.exe -mconsole");
  remove("./build/out.asm");
  remove("./build/out.obj");
}

ErrorType Compiler::validate(int argc, char* argv[]) {
  constexpr int REQUIRED_ARGS = 2;
  if (!Validation::has_valid_amount(argc, REQUIRED_ARGS)) {
    return ErrorType::INVALID_ARGC;
  }

  constexpr int FILE_LOCATION = 1;
  std::string file_path = argv[FILE_LOCATION];

  constexpr int MIN_FILE_NAME_LENGTH = 4;
  if (!Validation::has_required_length(file_path, MIN_FILE_NAME_LENGTH)) {
    return ErrorType::INVALID_FILE_PATH;
  }

  const std::string REQUIRED_FILE_TYPE = ".ae";
  if (!Validation::is_valid_file_type(file_path, REQUIRED_FILE_TYPE)) {
    return ErrorType::INVALID_FILE;
  }

  return ErrorType::NONE;
}

ErrorType Compiler::read_file(std::string file_path, std::string* output) {
  std::ifstream file(file_path);

  if (!file.is_open()) {
    return ErrorType::UNABLE_TO_READ;
  }

  std::stringstream buffer;
  buffer << file.rdbuf();

  *output = buffer.str();
  return ErrorType::NONE;
}

std::string Compiler::get_file_path(char* argv[]) {
  const int FILE_POSITION = 1;
  return argv[FILE_POSITION];
}
