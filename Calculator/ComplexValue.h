#pragma once
#include "CalculatedValue.h"

class ComplexValue : public CalculatedValue
{
    Complex value;

public:
    ComplexValue(std::string str);
    ComplexValue(std::string str, JsonContent& content);
    ComplexValue(Complex value);
    ~ComplexValue();

    CalculatedValue* operator+(CalculatedValue*& other) const override;
    CalculatedValue* operator-(CalculatedValue*& other) const override;
    CalculatedValue* operator*(CalculatedValue*& other) const override;
    CalculatedValue* operator/(CalculatedValue*& other) const override;
    CalculatedValue* operator^(CalculatedValue*& other) const override;
    CalculatedValue* operator-() const override;
    ExpressionType GetType() const override;
    void ConsolePrint() const override;
    Complex GetValue();
};

