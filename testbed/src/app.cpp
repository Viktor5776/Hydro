#include "app.h"
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <iostream>

App::App()
{
    glm::mat4 matrix(1.0f);
    glm::vec4 vector(1.0f);
    glm::vec4 result = matrix * vector;
    std::cout << result.x << ", " << result.y << ", " << result.z << ", " << result.w << std::endl;
}

void App::Update()
{
    
}

void App::Render()
{
    //Implement Graphics rendering here 
}

Hydro::app::Application* CreateApplication()
{
    return new App();
}