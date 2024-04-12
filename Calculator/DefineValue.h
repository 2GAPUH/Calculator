#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stack>

enum class expressionType {FLOAT, MATRIX, COMPLEX };

enum class CharType { NUMBER, VARIABLE, OPERATION, PARENTHESIS, UNDEFINE, POINT, SPACE };
enum class TokenType { NUMBER, VARIABLE, OPERATION, PARENTHESIS, UNDEFINED };
enum class OperationPriority { PLUS = 0, MINUS = 0, MULTIPLY = 1, DIVIDE = 1, DEGREE = 1, PARENTHESIS = -1};


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

    case TokenType::UNDEFINED:
        os << "undefine";
        break;

    default:
        os << "Unknown";
        break;
    }
    return os;
}

#define VALID true
#define INVALID false
#define NUM_ORDER false
#define OPER_ORDER true

#define DEBUG true
