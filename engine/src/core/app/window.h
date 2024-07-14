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
        void SetTitle( const std::string& title );
    private:
        SDL_Window* pWindow;
    };
}