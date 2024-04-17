#pragma once
#include "CalculatedValue.h"
#include "DefineValue.h"
#include "Token.h"

class FloatValue : public CalculatedValue
{
private:
	float value = 0;

public:
	FloatValue(Token* token);
	FloatValue(float value);
	CalculatedValue* operator+(const CalculatedValue& other) const override;
	CalculatedValue* operator-(const CalculatedValue& other) const override;
	CalculatedValue* operator*(const CalculatedValue& other) const override;
	CalculatedValue* operator/(const CalculatedValue& other) const override;
	CalculatedValue* operator^(const CalculatedValue& other) const override;
	ExpressionType GetExpressionType() const override;
};

