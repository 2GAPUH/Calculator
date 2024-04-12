#pragma once
#include "DefineValue.h"



class Token
{
private:
	std::string token;
	TokenType type;
	void SetToken(const std::string& str);

public:
	static CharType CheckCharType(char c);
	Token(std::string token);
	~Token();
	TokenType GetType();
	void ConsolePrint();
	std::string GetValue();
};

