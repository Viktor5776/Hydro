#include "app.h"

#include <iostream>

App::App()
{
    //Initialize game here
}

void App::Update()
{
    auto pos = mouse.GetPos();
    std::string title;
    title.append( "Mouse Position: " );
    title.append( std::to_string( pos.x ) );
    title.append( ", " );
    title.append( std::to_string( pos.y ) );
    window.SetTitle( title );

    //Test mouse input
    if( mouse.LeftIsDown() )
    {
        std::cout << "Left mouse button is down" << std::endl;
    }
    if( mouse.LeftIsUp() )
    {
        std::cout << "Left mouse button is up" << std::endl;
    }

    if( mouse.RightIsDown() )
    {
        std::cout << "Right mouse button is down" << std::endl;
    }
    if( mouse.RightIsUp() )
    {
        std::cout << "Right mouse button is up" << std::endl;
    }

    if( mouse.MiddleIsDown() )
    {
        std::cout << "Middle mouse button is down" << std::endl;
    }
    if( mouse.MiddleIsUp() )
    {
        std::cout << "Middle mouse button is up" << std::endl;
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