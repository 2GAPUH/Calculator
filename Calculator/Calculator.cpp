#include "Calculator.h"
#include "CalculatedValue.h"
#include "Token.h"

std::vector<Token*> Calculator::Parse(std::string& str)
{
    std::vector<Token*> parseVect;

    if (str.empty())
        return parseVect;

    std::string tmp;

    CharType lastType = Token::CheckCharType(str[0]);
    for (char ch : str)
    {
        CharType curType = Token::CheckCharType(ch);

        if (curType == CharType::UNDEFINE || curType == CharType::SPACE || (lastType == CharType::NUMBER || lastType == CharType::POINT) &&
            (curType == CharType::NUMBER || curType == CharType::POINT) || lastType == curType)
        {
            tmp += ch;
        }
        else
        {
            parseVect.push_back(new Token(tmp));
            tmp.clear();
            tmp += ch;
        }

        lastType = curType;
    }

    parseVect.push_back(new Token(tmp));

    return parseVect;
}



bool Calculator::CheckValid(std::vector<Token*> vect)
{
    int parenthesisOpen = 0;
    bool order = NUM_ORDER;

    for (auto token : vect)
    {
        switch (token->GetType())
        {
        case TokenType::PARENTHESIS:
            if (token->GetValue() == std::string("("))
                parenthesisOpen++;
            else
                parenthesisOpen--;
            if (parenthesisOpen < 0)
                return INVALID;
            break;

        case TokenType::NUMBER:
        case TokenType::VARIABLE:
            if (NUM_ORDER == order)
                order = OPER_ORDER;
            else
                return INVALID;
            break;

        case TokenType::UNDEFINED:
            break;

        case TokenType::OPERATION:
            if (OPER_ORDER == order)
                order = NUM_ORDER;
            else
                return INVALID;
            break;
        }
    }

    if (order == NUM_ORDER)
        return INVALID;

    return VALID;
}

void Calculator::RPN(std::vector<Token*>& vect)
{
    std::vector<Token*> tmpVect;
    std::stack<Token*> stack;

    for (auto token : vect)
    {
        switch (token->GetType())
        {
        case TokenType::NUMBER:
        case TokenType::VARIABLE:
            tmpVect.push_back(token);
            break;

        case TokenType::PARENTHESIS:
            if (token->GetValue() == std::string("("))
                stack.push(token);
            else
            {
                while (!stack.empty() && stack.top()->GetType() != TokenType::PARENTHESIS)
                {
                    tmpVect.push_back(stack.top());
                    stack.pop();
                }
                if (!stack.empty())
                    stack.pop();
            }
            break;

        case TokenType::OPERATION:
            while (!stack.empty() && CheckPriority(stack.top()->GetValue()[0]) >= CheckPriority(token->GetValue()[0]))
            {
                tmpVect.push_back(stack.top());
                stack.pop();
            }
            stack.push(token);
            break;

        case TokenType::UNDEFINED:
            break;
        }
    }

    while (!stack.empty()) {
        tmpVect.push_back(stack.top());
        stack.pop();
    }

    vect.clear();
    for (auto tmp : tmpVect)
        vect.push_back(tmp);
}

OperationPriority Calculator::CheckPriority(char c)
{
    switch (c)
    {
    case '+':
        return OperationPriority::PLUS;

    case '-':
        return OperationPriority::MINUS;

    case '*':
        return OperationPriority::MULTIPLY;

    case '/':
        return OperationPriority::DIVIDE;

    case '^':
        return OperationPriority::DEGREE;

    case '(':
    case ')':
        return OperationPriority::PARENTHESIS;
    }
}

void Calculator::calculate(std::vector<Token*>& vect)
{
    std::stack<Token*> stack;
    for (auto n : vect)
    {
        switch (n->GetType())
        {
        case TokenType::NUMBER:
        case TokenType::VARIABLE:
            stack.push(n);
            break;

        case TokenType::OPERATION:
            CalculatedValue* tmp = nullptr;
            Token* var2 = stack.top();
            stack.pop();

            try
            {
                switch (n->GetValue()[0])
                {
                case '+':
                    tmp = Calculator::add(stack.top()->GetCalcValue(), var2->GetCalcValue());
                    break;

                case '-':
                    tmp = Calculator::substract(stack.top()->GetCalcValue(), var2->GetCalcValue());
                    break;

                case '*':
                    tmp = Calculator::multiply(stack.top()->GetCalcValue(), var2->GetCalcValue());
                    break;

                case '/':
                    tmp = Calculator::devide(stack.top()->GetCalcValue(), var2->GetCalcValue());
                    break;

                case '^':
                    tmp = Calculator::power(stack.top()->GetCalcValue(), var2->GetCalcValue());
                    break;
                }
            }
            catch (const ErrorsType error)
            {
                std::cout << error << std::endl;
                return;
            }

            stack.top()->SetCalcValue(tmp);
            break;
        }
    }

    std::cout << "Expression value:\n";
    stack.top()->GetCalcValue()->ConsolePrint();
}

CalculatedValue* Calculator::add(CalculatedValue* a, CalculatedValue* b)
{
    if (a->GetType() == ExpressionType::FLOAT)
    {
        if (b->GetType() == ExpressionType::FLOAT)
            return *a + b;
        else
            return *b + a;
    }
    else if (a->GetType() == ExpressionType::MATRIX || a->GetType() == ExpressionType::COMPLEX)
    {
        return *a + b;
    }
}

CalculatedValue* Calculator::substract(CalculatedValue* a, CalculatedValue* b)
{
    if (a->GetType() == ExpressionType::FLOAT)
    {
        if (b->GetType() == ExpressionType::FLOAT)
            return *a - b;
        else
            return -*(*b - a);
    }
    else if (a->GetType() == ExpressionType::MATRIX || a->GetType() == ExpressionType::COMPLEX)
    {
        return *a - b;
    }
}

CalculatedValue* Calculator::multiply(CalculatedValue* a, CalculatedValue* b)
{
    if (a->GetType() == ExpressionType::FLOAT)
    {
        if (b->GetType() == ExpressionType::FLOAT)
            return *a * b;
        else
            return *b * a;
    }
    else if (a->GetType() == ExpressionType::MATRIX || a->GetType() == ExpressionType::COMPLEX)
    {
        return *a * b;
    }
}

CalculatedValue* Calculator::devide(CalculatedValue* a, CalculatedValue* b)
{
    if (a->GetType() == ExpressionType::FLOAT)
    {
        if (b->GetType() == ExpressionType::FLOAT)
            return *a / b;
        else
            return *b / a; 
    }
    else if (a->GetType() == ExpressionType::MATRIX || a->GetType() == ExpressionType::COMPLEX)
    {
        return *a / b;
    }
}

CalculatedValue* Calculator::power(CalculatedValue* a, CalculatedValue* b)
{
    if (a->GetType() == ExpressionType::FLOAT)
    {
        if (b->GetType() == ExpressionType::FLOAT)
            return *a ^ b;
        else
            throw(ErrorsType::FLOAT_POWER_UNDEFINE);
    }
    else if (a->GetType() == ExpressionType::MATRIX || a->GetType() == ExpressionType::COMPLEX)
    {
        return *a ^ b;
    }
}

void Calculator::DataProcessing(std::string& str)
{
    std::vector<Token*> parseVect = Parse(str);

    if (DEBUG)
        for (auto n : parseVect)
            n->ConsolePrint();

    if (!CheckValid(parseVect))
    {
        std::cout << "Invalid mathematic expresion!" << std::endl;

        for (Token* token : parseVect)
            delete token;

        parseVect.clear();

        return;
    }

    RPN(parseVect);

    if (DEBUG)
    {
        for (auto n : parseVect)
            std::cout << n->GetValue() << " ";

        std::cout << std::endl;
    }

    calculate(parseVect);

    for (Token* token : parseVect)
        delete token;

    parseVect.clear();
}
