#include "keyboard.h"
#include <SDL2/SDL.h>

namespace Hydro::app
{ 
    void Keyboard::HandleEvent( const SDL_Event& event )
    {
        if( event.key.repeat && !autoRepeatEnabled )
        {
            return;
        }

        KeyCode key = static_cast<KeyCode>(event.key.keysym.scancode);

        if( event.type == SDL_KEYDOWN )
        {
            currentKeys[key] = true;
            downKeys[key] = true;
        }
        else if( event.type == SDL_KEYUP )
        {
            currentKeys[key] = false;
            upKeys[key] = true;
        }
    }

    void Keyboard::EndFrame()
    {
        upKeys.clear();
        downKeys.clear();
    }
    
    bool Keyboard::GetKey( unsigned char keycode )
    {
        return GetKey( TranslateKey( keycode ) );
    }

    bool Keyboard::GetKey( KeyCode keycode )
    {
        return currentKeys[keycode];
    }

    bool Keyboard::KeyIsDown( unsigned char keycode )
    {
        return KeyIsDown( TranslateKey( keycode ) );
    }

    bool Keyboard::KeyIsDown( KeyCode keycode )
    {
        return downKeys[keycode];
    }

    bool Keyboard::KeyIsUp( unsigned char keycode )
    {
        return KeyIsUp( TranslateKey( keycode ) );
    }

    bool Keyboard::KeyIsUp( KeyCode keycode )
    {
        return upKeys[keycode];
    }
    
    KeyCode Keyboard::TranslateKey( unsigned char key )
    {
        if (key >= 'a' && key <= 'z') 
        {
            key = key - 'a' + 'A'; // Convert to uppercase
        }
        if (key >= 'A' && key <= 'Z') 
        {
            return static_cast<KeyCode>(SDL_SCANCODE_A + (key - 'A'));
        }
        
        return static_cast<KeyCode>(SDL_SCANCODE_UNKNOWN);
    }

    void Keyboard::EnableAutoRepeatKeys()
    {
        autoRepeatEnabled = true;
    }

    void Keyboard::DisableAutoRepeatKeys()
    {
        autoRepeatEnabled = false;
    }
}