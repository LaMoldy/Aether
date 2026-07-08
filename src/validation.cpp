#include <string>
#include <validation.hpp>

bool Validation::has_valid_amount(int amount, int required) {
  return amount == required;
}

bool Validation::has_required_length(std::string value, int required_length) {
  return value.length() >= required_length;
}

bool Validation::is_valid_file_type(std::string file,
                                    std::string expected_type) {
  return file.ends_with(expected_type);
}
