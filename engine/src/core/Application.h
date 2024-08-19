#pragma once
#include "Defines.h"
#include "Window.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "../gfx/IGraphics.h"
#include <string>
#include <memory>


namespace Hydro
{
    class HAPI Application
    {
    public:
        Application( int width = 1280, int height = 720, const std::string& title = "Hydro Application" );
        virtual ~Application() = default;
        void Run();
    private:
        virtual void Update() = 0;
        virtual void Render() = 0;
    protected:
        Window window;
        Input::Keyboard keyboard;
        Input::Mouse mouse;
        std::unique_ptr<gfx::IGraphics> pGraphics;
    };
}