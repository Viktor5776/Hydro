#pragma once
#include "application.h"
#include <iostream>

extern Hydro::app::Application* CreateApplication();

int main()
{
    auto app = CreateApplication();
    try
    {
        app->Run();
    }
    catch( const std::exception& e )
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}