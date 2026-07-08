#include <gtest/gtest.h>

#include <vector>

#include "../include/lexer.hpp"
#include "../include/token.hpp"

TEST(LexerTestSuite, TestTokenize) {
  using namespace std::string_literals;

  Lexer lexer = Lexer("return 1;\0"s);
  std::vector<Token> tokens = lexer.tokenize();
  EXPECT_EQ(tokens.at(0).to_str(), "Token Type: Return keyword, Value: return");
  EXPECT_EQ(tokens.at(1).to_str(), "Token Type: Number, Value: 1");
  EXPECT_EQ(tokens.at(2).to_str(), "Token Type: Semi Colon, Value: ;");
  EXPECT_EQ(tokens.at(3).to_str(), "Token Type: EOF, Value: \0"s);
}