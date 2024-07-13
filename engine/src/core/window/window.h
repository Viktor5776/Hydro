#pragma once
#include <string>
#include "defines.h"

struct SDL_Window;

namespace Hydro::win
{
    class HAPI Window
    {
    public:
        Window( int width = 1280, int height = 720, const std::string& title = "Hydro Application" );
        ~Window();
    private:
        SDL_Window* m_window;
    };
}