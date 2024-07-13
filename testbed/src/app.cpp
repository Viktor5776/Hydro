#include "app.h"

App::App()
{
    //Initialize game here
}

void App::Update()
{
    //Update game logic here
}

void App::Render()
{
    //Implement Graphics rendering here
}

Hydro::app::Application* CreateApplication()
{
    return new App();
}