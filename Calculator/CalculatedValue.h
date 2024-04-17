#pragma once
#include "DefineValue.h"

class CalculatedValue
{
protected:
	virtual CalculatedValue* operator+(const CalculatedValue& other) const = 0;
	virtual CalculatedValue* operator-(const CalculatedValue& other) const = 0;
	virtual CalculatedValue* operator*(const CalculatedValue& other) const = 0;
	virtual CalculatedValue* operator/(const CalculatedValue& other) const = 0;
	virtual CalculatedValue* operator^(const CalculatedValue& other) const = 0;
	virtual ExpressionType GetExpressionType() const = 0;
};

