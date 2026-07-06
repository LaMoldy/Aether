#include <errors.hpp>
#include <iostream>

void Error::print_usage()
{
    std::cout << "Usage: aether <file>.ae" << std::endl;
}

void Error::print_error(ErrorType type)
{
    std::string message = Error::get_errortype_message(type);
    std::cout << message << std::endl;

    if (Error::needs_usage_message(type))
    {
        print_usage();
    }
}

std::string Error::get_errortype_message(ErrorType type)
{
    std::string message;
    switch (type)
    {
        case ErrorType::INVALID_ARGC:
            message =
                "Error: Invalid amount of arguments passed to the compiler";
            return message;
        case ErrorType::INVALID_FILE_PATH:
            message = "Error: Invalid file provided to the compiler";
            return message;
        case ErrorType::INVALID_FILE:
            message = "Error: Invalid file type provided to the compiler";
            return message;
        case ErrorType::UNABLE_TO_READ:
            message = "Error: Could not find or read the file provided.";
            return message;
        default:
            message = "Error: Something has gone wrong, please try again.";
            return message;
    }
}

bool Error::needs_usage_message(ErrorType type)
{
    switch (type)
    {
        case ErrorType::INVALID_ARGC:
            return true;
        case ErrorType::INVALID_FILE_PATH:
            return true;
        case ErrorType::INVALID_FILE:
            return true;
        case ErrorType::UNABLE_TO_READ:
            return false;
        default:
            return false;
    }
}
