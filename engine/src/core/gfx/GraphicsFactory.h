#pragma once
#include "IGraphics.h"
#include <memory>

namespace Hydro::gfx
{
    class HAPI GraphicsFactory
    {
    public:
        enum class GraphicsType
        {
            Vulkan
        };

        static std::unique_ptr<IGraphics> CreateGraphics( GraphicsType type );
    };

    #define CREATE_VULKAN_GRAPHICS Hydro::gfx::GraphicsFactory::CreateGraphics( Hydro::gfx::GraphicsFactory::GraphicsType::Vulkan )
}