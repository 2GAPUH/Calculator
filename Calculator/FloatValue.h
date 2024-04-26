#pragma once
#include "CalculatedValue.h"

class Token;

class FloatValue : public CalculatedValue
{
private:
    float value = 0.f;

public:
    FloatValue(std::string str);
    FloatValue(Token  token);
    FloatValue(float i = 0);

    CalculatedValue* operator+(CalculatedValue*& other) const override;
    CalculatedValue* operator-(CalculatedValue*& other) const override;
    CalculatedValue* operator*(CalculatedValue*& other) const override;
    CalculatedValue* operator/(CalculatedValue*& other) const override;
    CalculatedValue* operator^(CalculatedValue*& other) const override;
    CalculatedValue* operator-() const override;
    ExpressionType GetType() const override;
    float GetValue();
    void ConsolePrint() const override;
};

