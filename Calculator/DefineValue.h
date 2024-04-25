#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>

enum class ExpressionType {FLOAT, MATRIX, COMPLEX };

enum class CharType { NUMBER, VARIABLE, OPERATION, PARENTHESIS, UNDEFINE, POINT, SPACE };
enum class TokenType { NUMBER, VARIABLE, OPERATION, PARENTHESIS, UNDEFINED };
enum class OperationPriority { PLUS = 0, MINUS = 0, MULTIPLY = 1, DIVIDE = 1, DEGREE = 1, PARENTHESIS = -1};

static ExpressionType expressionType = ExpressionType::FLOAT;

enum class ErrorsType {ZERO_DEVIDE, POWER_OVERFLOW, INCOMPATIBLE_MATRIX_SIZES, MATRIX_DIVIDE_MATRIX, MATRIX_POWER_MATRIX};

static std::ostream& operator<<(std::ostream& os, ErrorsType error) 
{
    switch (error) {
    case ErrorsType::ZERO_DEVIDE:
        os << "Zero Divide";
        break;
    case ErrorsType::POWER_OVERFLOW:
        os << "Power Overflow";
        break;
    case ErrorsType::INCOMPATIBLE_MATRIX_SIZES:
        os << "Incompatible Matrix Sizes";
        break;
    case ErrorsType::MATRIX_DIVIDE_MATRIX:
        os << "Matrix Divide Matrix";
        break;
    case ErrorsType::MATRIX_POWER_MATRIX:
        os << "Matrix Power Matrix";
        break;
    default:
        os << "Unknown Error";
        break;
    }
    return os;
}

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
