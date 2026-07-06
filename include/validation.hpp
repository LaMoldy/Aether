#pragma once

#include <string>

class Validation
{
public:
    static bool has_valid_amount(int amount, int required);
    static bool is_valid_file_type(std::string file, std::string expected_type);
    static bool has_required_length(std::string value, int required_length);
};
