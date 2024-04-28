#pragma once
#include "DefineValue.h"


class CalculatedValue;
class Token;

class Calculator
{
private:
	static bool CheckValid(std::vector<Token*> vect);
	static void RPN(std::vector<Token*>& vect);
	static OperationPriority CheckPriority(char c);
	static void calculate(std::vector<Token*>& vect);

public:
	static CalculatedValue* add(CalculatedValue* a, CalculatedValue* b);

	static CalculatedValue* substract(CalculatedValue* a, CalculatedValue* b);

	static CalculatedValue* multiply(CalculatedValue* a, CalculatedValue* b);

	static CalculatedValue* devide(CalculatedValue* a, CalculatedValue* b);

	static CalculatedValue* power(CalculatedValue* a, CalculatedValue* b);

	static void DataProcessing(std::vector<Token*>& parseVect);
};

