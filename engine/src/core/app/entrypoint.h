#include "application.h"

extern Hydro::app::Application* CreateApplication();

int main()
{
    auto app = CreateApplication();
    app->Run();
    return 0;
}