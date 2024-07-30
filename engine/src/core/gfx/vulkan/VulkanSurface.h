#pragma once
#include <vulkan/vulkan.h>
#include "VulkanInstance.h"
#include <SDL2/SDL.h>
#include <memory>

namespace Hydro::gfx
{
    class VulkanSurface
    {
    public:
        VulkanSurface( std::shared_ptr<VulkanInstance>  instance, SDL_Window* pWindow );
        ~VulkanSurface();
        VkSurfaceKHR GetSurface() const;
    private:
        std::shared_ptr<VulkanInstance> instance;
        VkSurfaceKHR surface;
    };
}