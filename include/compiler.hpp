#pragma once

#include <errors.hpp>
#include <string>


class Compiler {
 public:
  static void init(int argc, char* argv[]);

 private:
  static ErrorType validate(int argc, char* argv[]);
  static ErrorType read_file(std::string file_path, std::string* output);
  static std::string get_file_path(char* argv[]);
};
