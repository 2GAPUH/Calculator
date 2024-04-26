#include "Calculator.h"
#include "CalculatedValue.h"

CalculatedValue* Calculator::add(CalculatedValue* a, CalculatedValue* b)
{
    if (a->GetType() == ExpressionType::FLOAT)
    {
        if (b->GetType() == ExpressionType::FLOAT)
            return *a + b;
        else
            return *b + a;
    }
    else if (a->GetType() == ExpressionType::MATRIX || a->GetType() == ExpressionType::COMPLEX)
    {
        return *a + b;
    }
}

CalculatedValue* Calculator::substract(CalculatedValue* a, CalculatedValue* b)
{
    if (a->GetType() == ExpressionType::FLOAT)
    {
        if (b->GetType() == ExpressionType::FLOAT)
            return *a - b;
        else
            return -*(*b - a);
    }
    else if (a->GetType() == ExpressionType::MATRIX || a->GetType() == ExpressionType::COMPLEX)
    {
        return *a - b;
    }
}

CalculatedValue* Calculator::multiply(CalculatedValue* a, CalculatedValue* b)
{
    if (a->GetType() == ExpressionType::FLOAT)
    {
        if (b->GetType() == ExpressionType::FLOAT)
            return *a * b;
        else
            return *b * a;
    }
    else if (a->GetType() == ExpressionType::MATRIX || a->GetType() == ExpressionType::COMPLEX)
    {
        return *a * b;
    }
}

CalculatedValue* Calculator::devide(CalculatedValue* a, CalculatedValue* b)
{
    if (a->GetType() == ExpressionType::FLOAT)
    {
        if (b->GetType() == ExpressionType::FLOAT)
            return *a / b;
        else
            return *b / a; 
    }
    else if (a->GetType() == ExpressionType::MATRIX || a->GetType() == ExpressionType::COMPLEX)
    {
        return *a / b;
    }
}

CalculatedValue* Calculator::power(CalculatedValue* a, CalculatedValue* b)
{
    if (a->GetType() == ExpressionType::FLOAT)
    {
        if (b->GetType() == ExpressionType::FLOAT)
            return *a ^ b;
        else
            throw(ErrorsType::FLOAT_POWER_UNDEFINE);
    }
    else if (a->GetType() == ExpressionType::MATRIX || a->GetType() == ExpressionType::COMPLEX)
    {
        return *a ^ b;
    }
}
