#include "app.h"

#include <iostream>


App::App()
{
    //Initialize game here
}

void App::Update()
{
    if( keyboard.KeyIsDown( Hydro::app::KeyCode::ESCAPE))
    {
        std::cout << "Escape" << std::endl;
    }

    if( keyboard.GetKey( Hydro::app::KeyCode::SPACE))
    {
        std::cout << "Space" << std::endl;
    }

    if( keyboard.KeyIsDown( Hydro::app::KeyCode::CAPSLOCK))
    {
        std::cout << "Caps" << std::endl;
    }

    if( keyboard.KeyIsDown( Hydro::app::KeyCode::F8))
    {
        std::cout << "F8" << std::endl;
    }

    if( keyboard.KeyIsDown( Hydro::app::KeyCode::LCTRL))
    {
        std::cout << "Left Control" << std::endl;
    }

    if( keyboard.KeyIsDown( Hydro::app::KeyCode::RCTRL))
    {
        std::cout << "Right Control" << std::endl;
    }

    if( keyboard.KeyIsDown( Hydro::app::KeyCode::LALT))
    {
        std::cout << "Left Alt" << std::endl;
    }

    if( keyboard.KeyIsDown( Hydro::app::KeyCode::RALT))
    {
        std::cout << "Right Alt" << std::endl;
    }

    if( keyboard.KeyIsDown( Hydro::app::KeyCode::LSHIFT))
    {
        std::cout << "Left Shift" << std::endl;
    }
    
    if( keyboard.KeyIsDown( Hydro::app::KeyCode::RSHIFT))
    {
        std::cout << "Right Shift" << std::endl;
    }

    if( keyboard.KeyIsDown('W'))
    {
        std::cout << "W" << std::endl;
    
    }
}

void App::Render()
{
    //Implement Graphics rendering here
}

Hydro::app::Application* CreateApplication()
{
    return new App();
}