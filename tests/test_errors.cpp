#include <gtest/gtest.h>

#include <sstream>

#include "../include/errors.hpp"

class ErrorTestSuite : public ::testing::Test
{
   protected:
    std::stringstream buffer;
    std::streambuf* old = nullptr;

    void SetUp() override { old = std::cout.rdbuf(buffer.rdbuf()); }

    void TearDown() override { std::cout.rdbuf(old); }
};

TEST_F(ErrorTestSuite, PrintErrorInvalidArgc)
{
    Error::print_error(ErrorType::INVALID_ARGC);
    EXPECT_EQ(buffer.str(),
              "Error: Invalid amount of arguments passed to the compiler\n"
              "Usage: molgyc <file>.mgy\n");
}

TEST_F(ErrorTestSuite, PrintErrorInvalidFile)
{
    Error::print_error(ErrorType::INVALID_FILE);
    EXPECT_EQ(buffer.str(),
              "Error: Invalid file type provided to the compiler\n"
              "Usage: molgyc <file>.mgy\n");
}

TEST_F(ErrorTestSuite, PrintErrorInvalidFilePath)
{
    Error::print_error(ErrorType::INVALID_FILE_PATH);
    EXPECT_EQ(buffer.str(),
              "Error: Invalid file provided to the compiler\n"
              "Usage: molgyc <file>.mgy\n");
}

TEST_F(ErrorTestSuite, PrintDefaultError)
{
    Error::print_error(ErrorType::NONE);
    EXPECT_EQ(buffer.str(),
              "Error: Something has gone wrong, please try again.\n");
}
