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