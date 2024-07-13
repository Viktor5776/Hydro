#include "application.h"
#include <SDL2/SDL.h>

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
        SDL_Event event;

        while( running )
        {
            while( SDL_PollEvent( &event ) )
            {
                if( event.type == SDL_QUIT )
                {
                    running = false;
                }
                
                //TODO: Handle more events for keybord input and mouse input)
            }

            Update();
            Render();
        }
    }
}