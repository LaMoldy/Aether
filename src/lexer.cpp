#include <cctype>
#include <lexer.hpp>
#include <token.hpp>

Lexer::Lexer(std::string input)
{
    cursor = 0;
    character = 0;
    this->input = input;
}

void Lexer::remove_whitespace()
{
    while (std::isspace(character))
    {
        read_char();
    }
}

std::string Lexer::get_identifier()
{
    std::string result = "";
    while (std::isalpha(character) || character == '_')
    {
        result += character;
        read_char();
    }
    return result;
}

bool Lexer::is_keyword(std::string value) { return keywords.contains(value); }

TokenType Lexer::get_keyword_type(std::string value) { return keywords[value]; }

std::string Lexer::get_number()
{
    std::string result = "";
    while (std::isdigit(character))
    {
        result += character;
        read_char();
    }
    return result;
}

void Lexer::read_char()
{
    if (cursor > input.size())
    {
        character = 0;
    }
    else
    {
        character = input[cursor];
    }
    cursor++;
}

Token Lexer::next_token()
{
    remove_whitespace();
    std::string value = "";

    TokenType type;
    if ((character >= 'a' && character <= 'z') ||
        (character >= 'A' && character <= 'Z'))
    {
        value = get_identifier();

        if (is_keyword(value))
        {
            type = get_keyword_type(value);
        }
        else
        {
            type = TokenType::IDENTIFIER;
        }

        cursor--;
    }
    else if (character >= '0' && character <= '9')
    {
        value = get_number();
        type = TokenType::NUMBER;
        cursor--;
    }
    else
    {
        switch (character)
        {
            default:
                type = TokenType::ILLEGAL;
                break;
            case '{':
                type = TokenType::LCURLY;
                break;
            case '}':
                type = TokenType::RCURLY;
                break;
            case '(':
                type = TokenType::LPAREN;
                break;
            case ')':
                type = TokenType::RPAREN;
                break;
            case '=':
                type = TokenType::ASSIGN;
                break;
            case '+':
                type = TokenType::PLUS;
                break;
            case '-':
                type = TokenType::MINUS;
                break;
            case ';':
                type = TokenType::SEMICOLON;
                break;
            case ':':
                type = TokenType::COLON;
                break;
            case ',':
                type = TokenType::COMMA;
                break;
            case '"':
                type = TokenType::DQUOTES;
                break;
            case '\'':
                type = TokenType::QUOTES;
                break;
            case '\0':
                type = TokenType::END_OF_FILE;
                break;
        }
    }

    if (value == "")
    {
        value += character;
    }

    read_char();
    return Token(type, value);
}

std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens = std::vector<Token>();
    while (cursor <= input.size())
    {
        Token token = next_token();
        tokens.push_back(token);
    }
    return tokens;
}
