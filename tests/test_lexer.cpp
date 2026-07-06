#include <gtest/gtest.h>

#include <vector>

#include "../include/lexer.h"
#include "../include/token.h"


TEST(LexerTestSuite, TestTokenize) {
  using namespace std::string_literals;
  std::string str = "hello";

  Lexer lexer = Lexer("return 1;");
  std::vector<Token> tokens = lexer.tokenize();

  EXPECT_EQ(tokens.at(0).to_str(), "Token Type: EOF, Value: \0"s);
  EXPECT_EQ(tokens.at(1).to_str(), "Token Type: Identifier, Value: return");
  EXPECT_EQ(tokens.at(2).to_str(), "Token Type: Number, Value: 1");
  EXPECT_EQ(tokens.at(3).to_str(), "Token Type: Semi Colon, Value: ;");
}