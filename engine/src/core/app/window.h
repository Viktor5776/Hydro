#pragma once
#include <string>
#include "Defines.h"

struct SDL_Window;

namespace Hydro::app
{
    class HAPI Window
    {
    public:
        Window( int width, int height, const std::string& title );
        ~Window();
        void SetTitle( const std::string& title );
        SDL_Window* GetWindow() { return pWindow; }
    private:
        SDL_Window* pWindow;
    };
}