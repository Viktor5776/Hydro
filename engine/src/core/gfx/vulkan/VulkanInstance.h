#pragma once
#include <vulkan/vulkan.h>
#include <SDL2/SDL.h>

namespace Hydro::gfx
{
    class VulkanInstance
    {
    public:
        VulkanInstance( SDL_Window* pWindow );
        ~VulkanInstance();
        VkInstance GetInstance() const;
    private:
        VkInstance instance;
    };
}