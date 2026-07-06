#pragma once

#include <string>

enum class ErrorType : int
{
    NONE,
    INVALID_ARGC,
    INVALID_FILE_PATH,
    INVALID_FILE,
    UNABLE_TO_READ,
};

class Error
{
public:
    static void print_usage();
    static void print_error(ErrorType type);

private:
    static std::string get_errortype_message(ErrorType type);
    static bool needs_usage_message(ErrorType type);
};
