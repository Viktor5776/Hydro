#include "application.h"
#include <SDL2/SDL.h>

#include <vulkan/vulkan.h>
#include <iostream>

namespace Hydro::app
{
    Application::Application( int width, int height, const std::string& title )
        : 
        window( width, height, title )
    {
    }

    void Application::Run()
    {
        bool running = true;
        
        while( running )
        {
            SDL_Event event;
            while( SDL_PollEvent( &event ) )
            {
                switch( event.type )
                {
                    case SDL_QUIT:
                        running = false;
                        break;
                    case SDL_KEYDOWN:
                    case SDL_KEYUP:
                        keyboard.HandleEvent( event );
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                    case SDL_MOUSEBUTTONUP:
                    case SDL_MOUSEMOTION:
                        mouse.HandelEvent( event );
                        break;
                }
            }
            
            Update();
            Render();
            keyboard.EndFrame();
            mouse.EndFrame();
        }
    }
}