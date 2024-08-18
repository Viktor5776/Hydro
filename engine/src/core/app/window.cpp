#include <SDL2/SDL.h>
#include "Window.h"
#include "../log/Logger.h"

namespace Hydro::app
{
    Window::Window( int width, int height, const std::string& title )
    {
        if( SDL_Init( SDL_INIT_VIDEO ) != 0)
        {
            LOG_FATAL( "Failed to initialize SDL: " + std::string( SDL_GetError() ) );
        }

        //TODO: Change the Vulkan flag to only be used when using Vulkan backend
        pWindow = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE );

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