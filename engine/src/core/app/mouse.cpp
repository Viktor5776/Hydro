#include "mouse.h"
#include <SDL2/SDL.h>

namespace Hydro::app
{
    void Mouse::HandelEvent(SDL_Event& event)
    {
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                left[2] = true;
                left[1] = true;
                break;
            case SDL_BUTTON_RIGHT:
                right[2] = true;
                right[1] = true;
                break;
            case SDL_BUTTON_MIDDLE:
                middle[2] = true;
                middle[1] = true;
                break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                left[2] = false;
                left[0] = true;
                break;
            case SDL_BUTTON_RIGHT:
                right[2] = false;
                right[0] = true;
                break;
            case SDL_BUTTON_MIDDLE:
                middle[2] = false;
                middle[0] = true;
                break;
            }
            break;
        case SDL_MOUSEMOTION:
            delta = { event.motion.xrel, event.motion.yrel };
            pos = { event.motion.x, event.motion.y };
            break;
        }
    }

    void Mouse::EndFrame()
    {
        left[0] = false;
        right[0] = false;
        middle[0] = false;
        left[1] = false;
        right[1] = false;
        middle[1] = false;

        delta = { 0, 0 };
    }

    bool Mouse::GetLeft() const
    {
        return left[2];
    }

    bool Mouse::GetRight() const
    {
        return right[2];
    }

    bool Mouse::GetMiddle() const
    {
        return middle[2];
    }

    bool Mouse::LeftIsDown() const
    {
        return left[1];
    }

    bool Mouse::RightIsDown() const
    {
        return right[1];
    }

    bool Mouse::MiddleIsDown() const
    {
        return middle[1];
    }

    bool Mouse::LeftIsUp() const
    {
        return left[0];
    }

    bool Mouse::RightIsUp() const
    {
        return right[0];
    }

    bool Mouse::MiddleIsUp() const
    {
        return middle[0];
    }

    Mouse::Delta Mouse::GetDelta() const
    {
        return delta;
    }

    Mouse::Pos Mouse::GetPos() const
    {
        return pos;
    }
}