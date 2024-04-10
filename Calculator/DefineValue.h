#pragma once
#include <iostream>
#include <string>
#include <vector>

enum class expressionType {FLOAT, MATRIX, COMPLEX };

enum class CharType { NUMBER, VARIABLE, OPERATION, PARENTHESIS, UNDEFINE, POINT, SPACE };
enum class TokenType { NUMBER, VARIABLE, OPERATION, PARENTHESIS, UNDEFINE };

static std::ostream& operator<<(std::ostream& os, const TokenType& color)
{
    switch (color)
    {
    case TokenType::NUMBER:
        os << "number";
        break;

    case TokenType::VARIABLE:
        os << "variable";
        break;

    case TokenType::OPERATION:
        os << "operation";
        break;

    case TokenType::PARENTHESIS:
        os << "parenthesis";
        break;

    case TokenType::UNDEFINE:
        os << "undefine";
        break;

    default:
        os << "Unknown";
        break;
    }
    return os;
}