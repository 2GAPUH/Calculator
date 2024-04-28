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

std::vector<Token*> AppCore::Parse(std::string str)
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

std::vector<Token*> AppCore::Parse(JsonContent& content)
{
    std::vector<Token*> parseVect;

    if (content.str.empty())
        throw(ErrorsType::EMPTY_STRING);

    std::string tmp;

    CharType lastType = Token::CheckCharType(content.str[0]);
    for (char ch : content.str)
    {
        CharType curType = Token::CheckCharType(ch);

        if (curType == CharType::UNDEFINE || curType == CharType::SPACE || (lastType == CharType::NUMBER || lastType == CharType::POINT) &&
            (curType == CharType::NUMBER || curType == CharType::POINT) || lastType == curType)
        {
            tmp += ch;
        }
        else
        {
            parseVect.push_back(new Token(tmp, content));
            tmp.clear();
            tmp += ch;
        }

        lastType = curType;
    }

    parseVect.push_back(new Token(tmp));

    return parseVect;
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
    std::string str2 = "Invalid type!";
    bool flag = true;

    while (flag) 
    {
        std::cout << str1;

        try {
            int tmp;
            std::cin >> tmp;
            if (std::cin.fail())
                throw(ErrorsType::TRASH_INPUT);

            switch (tmp) {
            case 0:
                Token::SetExpressionType(ExpressionType::FLOAT);
                flag = false;
                break;

            case 1:
                Token::SetExpressionType(ExpressionType::MATRIX);
                flag = false;
                break;

            case 2:
                Token::SetExpressionType(ExpressionType::COMPLEX);
                flag = false;
                break;

            default:
                throw(ErrorsType::INVALID_TYPE);
                break;
            }
        }
        catch (const ErrorsType error) {
            std::cout << error;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

}

JsonContent AppCore::ReadFromJson(std::string path)
{
    JsonContent content;

    std::ifstream file("data.json");
    
    if (!file.is_open()) {
        throw(ErrorsType::JSON_FILE_CANT_OPEN);
    }

    std::string jsonString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();

    JSONCPP_STRING errors;

    Json::Value root;
    if (!reader->parse(jsonString.c_str(), jsonString.c_str() + jsonString.size(), &root, &errors)) {
        delete reader;
        throw(ErrorsType::JSON_PARCING_ERROR);
    }

    delete reader;

    std::string mode = root["mode"].asString();
    content.str = root["expression"].asString();
    content.variables = root["variables"];

    if (mode == "float")
        Token::SetExpressionType(ExpressionType::FLOAT);
    else if (mode == "matrix")
        Token::SetExpressionType(ExpressionType::MATRIX);
    else if (mode == "complex")
        Token::SetExpressionType(ExpressionType::COMPLEX);
    else
        throw(ErrorsType::INVALID_JSON_MODE);

    return content;
}

void AppCore::GetMode()
{
    std::string str = "0 - Console mode \n1 - Json mode \nSelect mode: ";
    int mode;
    bool flag = true;

    while(flag)
    {
        std::cout << str;

        std::string userInput;
        std::getline(std::cin, userInput);

        std::istringstream iss(userInput);
        if (iss >> mode)
        {
            switch (mode)
            {
            case 0:
                programMode = ProgramMode::CONSOLE;
                flag = false;
                break;

            case 1:
                programMode = ProgramMode::JSON;
                flag = false;
                break;

            default:
                std::cout << "Invalid mode\n";
                break;
            }
        }
        else
            std::cout << "Enter integer num\n";
    }
}

void AppCore::JsonMode()
{
    JsonContent content = ReadFromJson();

    std::vector<Token*> parseVect = Parse(content);

    Calculator::DataProcessing(parseVect);

    system("pause");
}

void AppCore::ConsoleMode()
{
    bool flag = true;

    GetExpressionType();

    while (flag)
    {
        std::cin.ignore();

        std::string str = GetString();

        std::vector<Token*> parseVect = Parse(str);

        Calculator::DataProcessing(parseVect);
    }
}

void AppCore::Start()
{
    GetMode();

    if (programMode == ProgramMode::JSON)
    {
        try{
            JsonMode();
        }
        catch (const ErrorsType error)
        {
            std::cout << error;
            programMode = ProgramMode::CONSOLE;
            std::cout << "Try console mode\n";
        }
        catch (const std::invalid_argument& e)
        {
            programMode = ProgramMode::CONSOLE;
            std::cout << "Try console mode\n";
            std::cerr << "Error converting string to floating point number: " << e.what() << std::endl;
        }
    }

    if (programMode == ProgramMode::CONSOLE)
    {
        ConsoleMode();
    }
}