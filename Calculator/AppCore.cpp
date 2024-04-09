#include "AppCore.h"

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

void AppCore::Start()
{
    while (true)
    {
    }
}
