#pragma once
#include "IGraphics.h"
#include <memory>
#include "../app/Window.h"

namespace Hydro::gfx
{
    class HAPI GraphicsFactory
    {
    public:
        enum class GraphicsType
        {
            Vulkan
        };

        //NOTE: May want to find a better way to pass parameters to the graphics API if there are diffrences between the APIs
        static std::unique_ptr<IGraphics> CreateGraphics( GraphicsType type, app::Window& window );
    };

    #define CREATE_VULKAN_GRAPHICS( window ) Hydro::gfx::GraphicsFactory::CreateGraphics( Hydro::gfx::GraphicsFactory::GraphicsType::Vulkan, window )
}