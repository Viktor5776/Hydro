#include <SDL2/SDL.h>
#include "window.h"
#include "../log/logger.h"

namespace Hydro::app
{
    Window::Window( int width, int height, const std::string& title )
    {
        pWindow = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN );

        if( pWindow == nullptr )
        {
            LOG_FATAL( "Failed to create window: " + std::string( SDL_GetError() ) );
        }
    }

    Window::~Window()
    {
        SDL_DestroyWindow( pWindow );
        SDL_Quit();
    }

    void Window::SetTitle( const std::string& title )
    {
        SDL_SetWindowTitle( pWindow, title.c_str() );
    }
}