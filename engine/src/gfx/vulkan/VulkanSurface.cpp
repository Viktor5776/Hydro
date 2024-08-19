#include "VulkanSurface.h"
#include <SDL2/SDL_vulkan.h>
#include <stdexcept>

namespace Hydro::gfx
{
    VulkanSurface::VulkanSurface( std::shared_ptr<VulkanInstance> instance, SDL_Window* pWindow )
        :
        instance( instance )
    {
        if( SDL_Vulkan_CreateSurface( pWindow, instance->GetInstance(), &surface ) == SDL_FALSE )
        {
            throw std::runtime_error( "Failed to create Vulkan surface!" );
        }
    }

    VulkanSurface::~VulkanSurface()
    {
        vkDestroySurfaceKHR( instance->GetInstance(), surface, nullptr );
    }

    VkSurfaceKHR VulkanSurface::GetSurface() const
    {
        return surface;
    }
}