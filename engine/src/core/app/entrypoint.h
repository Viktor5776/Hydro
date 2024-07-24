#pragma once
#include "application.h"
#include <iostream>
#include <stdexcept>

extern Hydro::app::Application* CreateApplication();

int main()
{
    try
    {
        auto app = CreateApplication();
        app->Run();
    }
    catch( const std::exception& e )
    {
        std::cerr << e.what() << std::endl;
        system("pause");
        return 1;
    }
    return 0;
}