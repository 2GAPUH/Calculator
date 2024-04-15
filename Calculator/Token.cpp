#include "Token.h"
#include "FloatValue.h"


void Token::SetToken(const std::string& str)
{
    const int size = str.size();
    bool flagPoint = false;

    CharType startType = CheckCharType(str[0]);

    if (startType == CharType::PARENTHESIS || startType == CharType::OPERATION)
    {
        token = str[0];
        switch (startType)
        {
        case CharType::OPERATION:
            type = TokenType::OPERATION;
            break;
        case CharType::PARENTHESIS:
            type = TokenType::PARENTHESIS;
            break;
        }
        return;
    }
    else if (startType == CharType::UNDEFINE)
    {
        token.clear();
        type = TokenType::UNDEFINED;
        return;
    }

    for (char ch : str)
    {
        CharType curType = CheckCharType(ch);

        if (startType != curType)
        {
            if (curType == CharType::UNDEFINE || curType == CharType::SPACE)
                continue;
            else if (startType == CharType::POINT && curType == CharType::NUMBER)
            {
                token += ch;
                continue;
            }
            else if (startType == CharType::NUMBER && curType == CharType::POINT && !flagPoint)
            {
                token += ch;
                flagPoint = true;
                continue;
            }
            else
            {
                token.clear();
                type = TokenType::UNDEFINED;
                return;
            }
        }
        else
        {
            token += ch;
        }
    }

    switch (startType)
    {
    case CharType::NUMBER:
    case CharType::POINT:
        type = TokenType::NUMBER;
        break;
    case CharType::VARIABLE:
        type = TokenType::VARIABLE;
        break;
    }
}

void Token::SetValue()
{
    if (type == TokenType::NUMBER)
    {
        value = new FloatValue(std::stof(token));
        return;
    }

    if(type == TokenType::VARIABLE)
    switch (expressionType)
    {
    case ExpressionType::FLOAT:
        value = new FloatValue(this);
        break;
    }
}


void Token::ConsolePrint()
{
    std::cout << "Token = '" << token << "'; Type = '" << type << "';" << std::endl;
}

std::string Token::GetValue()
{
    return token;
}

CharType Token::CheckCharType(char c)
{
    if (c == '*' || c == '-' || c == '+' || c == '/' || c == '^')
        return CharType::OPERATION;

    if (c == '(' || c == ')')
        return CharType::PARENTHESIS;

    if (c >= '0' && c <= '9')
        return CharType::NUMBER;

    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        return CharType::VARIABLE;

    if (c == '.' || c == ',')
        return CharType::POINT;

    if (c == ' ')
        return CharType::SPACE;

    return CharType::UNDEFINE;
}



Token::Token(std::string token)
{
	if (token.empty())
	{
		this->token = "";
		type = TokenType::UNDEFINED;
		return;
	}

	SetToken(token);
    SetValue();
}

Token::~Token()
{
}

TokenType Token::GetType()
{
    return type;
}
