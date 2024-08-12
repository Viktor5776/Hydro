#include "app.h"
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <iostream>
#include <core/gfx/GraphicsFactory.h>

App::App()
    :
    Application( WIDTH, HEIGHT, "Testbed" )
{
    pGraphics = CREATE_VULKAN_GRAPHICS( window );
}

void App::Update()
{
    //Frames per second
    
    float t = timer.Mark();
    float fps = 1.0f / t;

    acc += fps;

    if( index++ > 5000 )
    {
        std::cout << "FPS: " << acc/50000 << std::endl;
        std::cout << "Frame Time: " << 50000/acc << std::endl;
        index = 0;
        acc = 0.0f;
    }

}

void App::Render()
{
    //Implement Graphics rendering here 
    pGraphics->Render();
}

Hydro::app::Application* CreateApplication()
{
    return new App();
}