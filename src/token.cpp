#include <format>
#include <map>
#include <optional>
#include <token.hpp>

Token::Token(TokenType type, std::optional<std::string> value = std::nullopt)
{
    this->type = type;
    if (value.has_value())
    {
        this->value = value;
    }
}

std::string Token::to_str()
{
    std::string type = Token::token_type_to_str();
    std::string value = this->value.value_or("N/A");
    return std::format("Token Type: {}, Value: {}", type, value);
}

std::string Token::token_type_to_str()
{
    std::map<TokenType, std::string> token_types = {
        // Special Tokens
        {TokenType::ILLEGAL, "Illegal"},
        {TokenType::END_OF_FILE, "EOF"},

        // General
        {TokenType::IDENTIFIER, "Identifier"},
        {TokenType::NUMBER, "Number"},

        // Keywords
        {TokenType::FUNCTION, "Function Keyword"},
        {TokenType::IF, "If Keyword"},
        {TokenType::LET, "Let keyword"},
        {TokenType::PRINT, "Print keyword"},
        {TokenType::RETURN, "Return keyword"},
        {TokenType::INT, "Int Keyword"},

        // Punctuation
        {TokenType::ASSIGN, "Assign"},
        {TokenType::PLUS, "Plus"},
        {TokenType::MINUS, "Minus"},
        {TokenType::COMMA, "Comma"},
        {TokenType::SEMICOLON, "Semi Colon"},
        {TokenType::COLON, "Colon"},
        {TokenType::LPAREN, "Left Parenthesis"},
        {TokenType::RPAREN, "Right Parenthesis"},
        {TokenType::LCURLY, "Left Curly"},
        {TokenType::RCURLY, "Right Curly"},
        {TokenType::QUOTES, "Quotes"},
        {TokenType::DQUOTES, "Double Quotes"}};
    return token_types[type];
}
