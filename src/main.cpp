#include <compiler.hpp>
#include <iostream>

bool has_valid_amount_of_args(int argc) {
  const int REQUIRED_ARGS = 2;
  return argc >= REQUIRED_ARGS;
}

int main(int argc, char* argv[]) {
  // Validate the amount of args
  if (!has_valid_amount_of_args(argc)) {
    std::cout << "<compiler error>: Invalid amount of arguments passed to the "
                 "compiler"
              << std::endl;
    Compiler::print_usage();
    return EXIT_FAILURE;
  }

  // Get Source File
  const int source_file_index = 1;
  const std::string source_file = argv[source_file_index];

  // Run the compiler
  Compiler compiler(source_file);
  compiler.run();

  return EXIT_SUCCESS;
}
