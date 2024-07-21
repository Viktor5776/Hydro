#include "GraphicsFactory.h"
#include "vulkan/VulkanGraphics.h"


namespace Hydro::gfx
{
    std::unique_ptr<IGraphics> GraphicsFactory::CreateGraphics( GraphicsType type )
    {
        switch( type )
        {
        case GraphicsType::Vulkan:
            return std::make_unique<VulkanGraphics>();
        default:
            return nullptr;
        }
    }
}