#pragma once
#include "Application.h"
#include <iostream>
#include <stdexcept>

extern Hydro::Application* CreateApplication();

int main()
{
    try
    {
        auto app = CreateApplication();
        app->Run();
        delete app;
    }
    catch( const std::exception& e )
    {
        std::cerr << e.what() << std::endl;
        system("pause");
        return 1;
    }

    return 0;
}

