#pragma once
#include "DefineValue.h"

class Token;

class AppCore
{
#pragma region ST
private:
    AppCore();
    AppCore(AppCore&);
    AppCore(AppCore&&);
    static AppCore* instance;
    ~AppCore();
public:
    static AppCore* GetInstance();
    static void DestroyInstance();
#pragma endregion

private:
    std::string GetString();
    expressionType type;
    void GetExpressionType();
    std::vector<Token*> Parse(std::string& str);
    void RPN(std::vector<Token*>& vect);
    bool CheckValid(std::vector<Token*>& vect);
    OperationPriority CheckPriority(char c);

public:
    void Start();
};

