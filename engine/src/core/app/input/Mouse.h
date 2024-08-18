#pragma once
#include "Defines.h"

union SDL_Event;



namespace Hydro::app
{
    class HAPI Mouse
    {
    public:
        struct Delta
        {
            int x;
            int y;
        };
        typedef Delta Pos;
    public:
        void HandelEvent(SDL_Event& event);
        void EndFrame();
        bool GetLeft() const;
        bool GetRight() const;
        bool GetMiddle() const;
        bool LeftIsDown() const;
        bool RightIsDown() const;
        bool MiddleIsDown() const;
        bool LeftIsUp() const;
        bool RightIsUp() const;
        bool MiddleIsUp() const;
        Delta GetDelta() const;
        Pos GetPos() const;
    private:
        // 0 = up, 1 = down, 2 = current
        bool left[3] = { false, false, false };
        bool right[3] = { false, false, false };
        bool middle[3] = { false, false, false };
        Delta delta = { 0, 0 };
        Pos pos = { 0, 0 };
    };
}