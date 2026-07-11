#include <ast.hpp>
#include <token.hpp>

class Parser {
 public:
  Parser(const std::vector<Token>& tokens) : tokens(tokens), position(0) {}
  std::unique_ptr<Program> parse();

 private:
  const std::vector<Token>& tokens;
  int position;

  const Token& peek();
  void consume(TokenType expected);
  void advance();
  std::unique_ptr<Expression> parseExpression();
  std::unique_ptr<ReturnStatement> parseReturn();
};
