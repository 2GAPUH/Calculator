#pragma once
#include "DefineValue.h"

class CalculatedValue;

class Calculator
{
public:
	static CalculatedValue* add(CalculatedValue* a, CalculatedValue* b);

	static CalculatedValue* substract(CalculatedValue* a, CalculatedValue* b);

	static CalculatedValue* multiply(CalculatedValue* a, CalculatedValue* b);

	static CalculatedValue* devide(CalculatedValue* a, CalculatedValue* b);

	static CalculatedValue* power(CalculatedValue* a, CalculatedValue* b);
};

