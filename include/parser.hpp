#pragma once

#include <token.hpp>
#include <vector>

class Parser
{
public:
    std::vector<Token> tokens;

private:
    Token peek();
    Token consume();
};