#include "AppCore.h"
#include "Token.h"

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
            type = expressionType::FLOAT;
            break;

        case 1:
            type = expressionType::MATRIX;
            break;

        case 2:
            type = expressionType::COMPLEX;
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




void AppCore::Start()
{
    bool flag = true;

    GetExpressionType();

    while (flag)
    {
        std::cin.ignore();

        std::string str = GetString();

        std::cout << "You enter:" << str << std::endl;

        std::vector<Token*> parseVect = Parse(str);

        for (auto n : parseVect)
            n->ConsolePrint();

        for (Token* token : parseVect)
            delete token;

        parseVect.clear();
    }
}
