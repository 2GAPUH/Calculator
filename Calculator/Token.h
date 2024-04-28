#pragma once
#include "DefineValue.h"

class CalculatedValue;

class Token
{
private:
	std::string token;
	TokenType type;
	void SetToken(const std::string& str);
	void SetValue();
	void SetValue(JsonContent& content);
	CalculatedValue* calcValue = nullptr;

public:
	static CharType CheckCharType(char c);
	Token(std::string token);
	Token(std::string token, JsonContent& content);
	~Token();
	TokenType GetType();
	void ConsolePrint();
	std::string GetValue();
	CalculatedValue*& GetCalcValue();
	void SetCalcValue(CalculatedValue* calcValue);
	static void SetExpressionType(ExpressionType expressionType);
};

