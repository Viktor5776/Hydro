#pragma once
#include <string>
#include "defines.h"

struct SDL_Window;

namespace Hydro::app
{
    class HAPI Window
    {
    public:
        Window( int width, int height, const std::string& title );
        ~Window();
    private:
        SDL_Window* pWindow;
    };
}