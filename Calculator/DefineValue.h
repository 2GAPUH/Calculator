#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <json/json.h>
#include <fstream>

enum class ExpressionType {FLOAT, MATRIX, COMPLEX };

enum class CharType { NUMBER, VARIABLE, OPERATION, PARENTHESIS, UNDEFINE, POINT, SPACE };
enum class TokenType { NUMBER, VARIABLE, OPERATION, PARENTHESIS, UNDEFINED };
enum class OperationPriority { PLUS = 0, MINUS = 0, MULTIPLY = 1, DIVIDE = 1, DEGREE = 2, PARENTHESIS = -1};

enum class ErrorsType {ZERO_DEVIDE, POWER_OVERFLOW, INCOMPATIBLE_MATRIX_SIZES, MATRIX_DIVIDE_MATRIX, 
    MATRIX_POWER_MATRIX, FLOAT_POWER_UNDEFINE, TRASH_INPUT, INVALID_TYPE, COMPLEX_POWER_COMPLEX, JSON_FILE_CANT_OPEN,
    JSON_PARCING_ERROR, INVALID_JSON_MODE, EMPTY_STRING, UNDEFINED_VARIABLE, INVALID_MATRIX_SIZE, FIELD_ABSENCE, MATRIX_INIT_ERROR,
    UNNAMED_FIELD};

enum class ProgramMode { CONSOLE, JSON};

struct JsonContent
{
    std::string str;
    Json::Value variables;
};

static std::ostream& operator<<(std::ostream& os, ErrorsType error) 
{
    os << "ERROR! ";
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
    case ErrorsType::FLOAT_POWER_UNDEFINE:
        os << "A float can only be raised to the float degree";
        break;
    case ErrorsType::TRASH_INPUT:
        os << "Enter ONLY int num";
        break;
    case ErrorsType::INVALID_TYPE:
        os << "Invalid type. Try again";
        break;
    case ErrorsType::COMPLEX_POWER_COMPLEX:
        os << "Complex power complex";
        break;
    case ErrorsType::JSON_FILE_CANT_OPEN:
        os << "Opening json file";
        break;
    case ErrorsType::JSON_PARCING_ERROR:
        os << "Json parcing";
        break;
    case ErrorsType::INVALID_JSON_MODE:
        os << "Json invalid expression mode";
        break;
    case ErrorsType::EMPTY_STRING:
        os << "Empty string";
        break;
    case ErrorsType::UNDEFINED_VARIABLE:
        os << "Undefined variable";
        break;
    case ErrorsType::INVALID_MATRIX_SIZE:
        os << "Invalid matrix size";
        break;
    case ErrorsType::FIELD_ABSENCE:
        os << "Field absence";
        break;
    case ErrorsType::MATRIX_INIT_ERROR:
        os << "Matrix init error";
        break;
    case ErrorsType::UNNAMED_FIELD:
        os << "Field name empty";
        break;


    default:
        os << "Unknown Error";
        break;
    }

    os << std::endl;
    return os;
}

struct Complex
{
    float real = 0;
    float imag = 0;
};

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
