#pragma once
#include "DefineValue.h"



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

public:
    void Start();
};

