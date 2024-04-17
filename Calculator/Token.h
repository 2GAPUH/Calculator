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
	CalculatedValue* calcValue = nullptr;

public:
	static CharType CheckCharType(char c);
	Token(std::string token);
	~Token();
	TokenType GetType();
	void ConsolePrint();
	std::string GetValue();
	CalculatedValue*& GetCalcValue();
};

