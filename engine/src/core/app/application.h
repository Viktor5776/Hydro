#pragma once
#include "defines.h"
#include "window.h"
#include "keyboard.h"
#include <string>


namespace Hydro::app
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
        Keyboard keyboard;
    };
}