#pragma once

#include <token.h>

enum class Keywords : int { FUNCTION, PRINTLN, LET, IF, ELIF, ELSE, RETURN };
enum class Types : int { INT, BOOL, CHAR, STRING };

bool is_keyword(Token token);