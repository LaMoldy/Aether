#include <gtest/gtest.h>

#include "../include/token.h"


TEST(TokenTestSuite, TokenToStrIdentifier) {
  Token tok = Token(TokenType::IDENTIFIER, "Hello");
  std::string result = tok.to_str();
  std::string expected_result = "Token Type: Identifier, Value: Hello";
  EXPECT_EQ(result, expected_result);
}

TEST(TokenTestSuite, TokenToStrNumber) {
  Token tok = Token(TokenType::NUMBER, "10");
  std::string result = tok.to_str();
  std::string expected_result = "Token Type: Number, Value: 10";
  EXPECT_EQ(result, expected_result);
}

TEST(TokenTestSuite, TokenToStrAssign) {
  Token tok = Token(TokenType::ASSIGN, "=");
  std::string result = tok.to_str();
  std::string expected_result = "Token Type: Assign, Value: =";
  EXPECT_EQ(result, expected_result);
}

TEST(TokenTestSuite, TokenToStrPlus) {
  Token tok = Token(TokenType::PLUS, "+");
  std::string result = tok.to_str();
  std::string expected_result = "Token Type: Plus, Value: +";
  EXPECT_EQ(result, expected_result);
}

TEST(TokenTestSuite, TokenToStrMinus) {
  Token tok = Token(TokenType::MINUS, "-");
  std::string result = tok.to_str();
  std::string expected_result = "Token Type: Minus, Value: -";
  EXPECT_EQ(result, expected_result);
}

TEST(TokenTestSuite, TokenToStrComma) {
  Token tok = Token(TokenType::COMMA, ",");
  std::string result = tok.to_str();
  std::string expected_result = "Token Type: Comma, Value: ,";
  EXPECT_EQ(result, expected_result);
}

TEST(TokenTestSuite, TokenToStrSemiColon) {
  Token tok = Token(TokenType::SEMICOLON, ";");
  std::string result = tok.to_str();
  std::string expected_result = "Token Type: Semi Colon, Value: ;";
  EXPECT_EQ(result, expected_result);
}

TEST(TokenTestSuite, TokenToStrColon) {
  Token tok = Token(TokenType::COLON, ":");
  std::string result = tok.to_str();
  std::string expected_result = "Token Type: Colon, Value: :";
  EXPECT_EQ(result, expected_result);
}

TEST(TokenTestSuite, TokenToStrLParen) {
  Token tok = Token(TokenType::LPAREN, "[");
  std::string result = tok.to_str();
  std::string expected_result = "Token Type: Left Parenthesis, Value: [";
  EXPECT_EQ(result, expected_result);
}

TEST(TokenTestSuite, TokenToStrRParen) {
  Token tok = Token(TokenType::RPAREN, "]");
  std::string result = tok.to_str();
  std::string expected_result = "Token Type: Right Parenthesis, Value: ]";
  EXPECT_EQ(result, expected_result);
}

TEST(TokenTestSuite, TokenToStrLCurly) {
  Token tok = Token(TokenType::LCURLY, "{");
  std::string result = tok.to_str();
  std::string expected_result = "Token Type: Left Curly, Value: {";
  EXPECT_EQ(result, expected_result);
}

TEST(TokenTestSuite, TokenToStrRCurly) {
  Token tok = Token(TokenType::RCURLY, "}");
  std::string result = tok.to_str();
  std::string expected_result = "Token Type: Right Curly, Value: }";
  EXPECT_EQ(result, expected_result);
}

TEST(TokenTestSuite, TokenToStrQuotes) {
  Token tok = Token(TokenType::QUOTES, "'");
  std::string result = tok.to_str();
  std::string expected_result = "Token Type: Quotes, Value: '";
  EXPECT_EQ(result, expected_result);
}

TEST(TokenTestSuite, TokenToStrDQuotes) {
  Token tok = Token(TokenType::DQUOTES, "\"");
  std::string result = tok.to_str();
  std::string expected_result = "Token Type: Double Quotes, Value: \"";
  EXPECT_EQ(result, expected_result);
}