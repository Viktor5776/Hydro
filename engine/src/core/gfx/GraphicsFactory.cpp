#include "GraphicsFactory.h"
#include "vulkan/VulkanGraphics.h"


namespace Hydro::gfx
{
    std::unique_ptr<IGraphics> GraphicsFactory::CreateGraphics( GraphicsType type, app::Window& window )
    {
        switch( type )
        {
        case GraphicsType::Vulkan:
            return std::make_unique<VulkanGraphics>( window );
        default:
            return nullptr;
        }
    }
}