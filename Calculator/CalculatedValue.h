#pragma once
#include "DefineValue.h"

class CalculatedValue
{
public:
    virtual CalculatedValue* operator+(CalculatedValue*& other) const = 0;
    virtual CalculatedValue* operator-(CalculatedValue*& other) const = 0;
    virtual CalculatedValue* operator*(CalculatedValue*& other) const = 0;
    virtual CalculatedValue* operator/(CalculatedValue*& other) const = 0;
    virtual CalculatedValue* operator^(CalculatedValue*& other) const = 0;
    virtual CalculatedValue* operator-() const = 0;
    virtual ExpressionType GetType() const = 0;
    virtual void ConsolePrint() const = 0;
};