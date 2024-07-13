#include <core/window/window.h>
#include <iostream>

int main()
{
    Hydro::win::Window window(1280, 720, "Hydro Application");    

    while(true)
    {
        std::cout << "Running" << std::endl;
    }

    return 0;
}