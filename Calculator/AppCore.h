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
    std::vector<Token*> Parse(std::string str);
    std::vector<Token*> Parse(JsonContent& content);
    std::string GetString();
    void GetExpressionType();
    JsonContent ReadFromJson(std::string path = "data.json");
    void GetMode();
    void JsonMode();
    void ConsoleMode();
    ProgramMode programMode;

public:
    void Start();
};

