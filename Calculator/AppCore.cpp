#include "AppCore.h"
#include "Token.h"
#include "Calculator.h"
#include "CalculatedValue.h"

AppCore* AppCore::instance = nullptr;

AppCore::AppCore()
{
}

AppCore::~AppCore()
{
}

AppCore* AppCore::GetInstance()
{
    if (instance == nullptr)
        instance = new AppCore();
    return instance;
}

void AppCore::DestroyInstance()
{
    delete instance;
    instance = nullptr;
}

std::string AppCore::GetString()
{
    std::string str;
    std::cout << "Enter expression: ";
    std::getline(std::cin, str);
    return str;
}

void AppCore::GetExpressionType()
{
    std::string str1 = "0 - Float \n1 - Matrix \n2 - Complex \nEnter expression type: ";
    std::string str2 = "Invaid type!";
    int tmp = -1;
    bool flag = true;

    while (flag)
    {
        std::cout << str1;

        std::cin >> tmp;
        flag = false;

        switch (tmp)
        {
        case 0:
            expressionType = ExpressionType::FLOAT;
            break;

        case 1:
            expressionType = ExpressionType::MATRIX;
            break;

        case 2:
            expressionType = ExpressionType::COMPLEX;
            break;
        
        default:
            flag = true;
            std::cout << str2 << std::endl;
            break;
        }
    }

}

std::vector<Token*> AppCore::Parse(std::string& str)
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

void AppCore::RPN(std::vector<Token*>& vect)
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
                if(!stack.empty())
                    stack.pop();
            }
            break;

        case TokenType::OPERATION:
            while (!stack.empty() && CheckPriority(stack.top()->GetValue()[0]) >= CheckPriority(token->GetValue()[0]) )
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


bool AppCore::CheckValid(std::vector<Token*>& vect)
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

OperationPriority AppCore::CheckPriority(char c)
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

void AppCore::Calc(std::vector<Token*>& vect)
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

}

void AppCore::Start()
{
    bool flag = true;

    GetExpressionType();

    while (flag)
    {
        std::cin.ignore();

        std::string str = GetString();

        if(DEBUG)
            std::cout << "You enter:" << str << std::endl;

        std::vector<Token*> parseVect = Parse(str);

        if(DEBUG)
            for (auto n : parseVect)
                n->ConsolePrint();

        if (!CheckValid(parseVect))
        {
            std::cout << "Invalid mathematic expresion!" << std::endl;
         
            for (Token* token : parseVect)
                delete token;

            parseVect.clear();

            continue;
        }

        RPN(parseVect);
        
        if (DEBUG)
        {
            for (auto n : parseVect)
                std::cout << n->GetValue() << " ";
                
            std::cout << std::endl;
        }

        Calc(parseVect);

        for (Token* token : parseVect)
            delete token;

        parseVect.clear();
    }
}
//3 + 2 - ( 10 ^ 4) / 5