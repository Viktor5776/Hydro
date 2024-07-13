#include <SDL2/SDL.h>
#include "window.h"
#include "../log/logger.h"

namespace Hydro::win
{
    Window::Window( int width, int height, const std::string& title )
    {
        m_window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN );

        if( m_window == nullptr )
        {
            LOG_FATAL( "Failed to create window: " + std::string( SDL_GetError() ) );
        }
    }

    Window::~Window()
    {
        SDL_DestroyWindow( m_window );
        SDL_Quit();
    }
}