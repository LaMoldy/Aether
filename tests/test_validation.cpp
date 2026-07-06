#include <gtest/gtest.h>

#include "../include/validation.h"


TEST(ValidationTestSuite, HasValidAmount_VALID) {
  bool result = Validation::has_valid_amount(5, 5);
  bool expected = true;
  EXPECT_EQ(result, expected);
}

TEST(ValidationTestSuite, HasValidAmountGreater) {
  bool result = Validation::has_valid_amount(10, 5);
  bool expected = false;
  EXPECT_EQ(result, expected);
}

TEST(ValidationTestSuite, HasValidAmount_INVALID) {
  bool result = Validation::has_valid_amount(2, 3);
  bool expected = false;
  EXPECT_EQ(result, expected);
}

TEST(ValidationTestSuite, HasRequiredLength_INVALID) {
  bool result = Validation::has_required_length("hello", 7);
  bool expected = false;
  EXPECT_EQ(result, expected);
}

TEST(ValidationTestSuite, HasRequiredLength_EQUAL) {
  bool result = Validation::has_required_length("world", 5);
  bool expected = true;
  EXPECT_EQ(result, expected);
}

TEST(ValidationTestSuite, HasRequiredLength_Greater) {
  bool result = Validation::has_required_length("hello, world", 4);
  bool expected = true;
  EXPECT_EQ(result, expected);
}

TEST(ValidationTestSuite, IsValidFileType_Valid) {
  bool result = Validation::is_valid_file_type("a.mgy", ".mgy");
  bool expected = true;
  EXPECT_EQ(result, expected);
}

TEST(ValidationTestSuite, IsValidFileType_InValid) {
  bool result = Validation::is_valid_file_type("b.mgx", ".mgy");
  bool expected = false;
  EXPECT_EQ(result, expected);
}

TEST(ValidationTestSuite, ISValidFileType_Equal) {
  bool result = Validation::is_valid_file_type(".mgy", ".mgy");
  bool expected = true;
  EXPECT_EQ(result, expected);
}
