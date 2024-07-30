#pragma once
#include "../IGraphics.h"
#include <vulkan/vulkan.h>
#include <SDL2/SDL.h>
#include <memory>
#include "VulkanDebuger.h"
#include "VulkanInstance.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanDevice.h"
#include "VulkanQueue.h"
#include "VulkanSurface.h"

namespace Hydro::gfx
{
    class VulkanGraphics : public IGraphics
    {
    public:
        VulkanGraphics( app::Window& window );
        ~VulkanGraphics() override;
        void Render() override;
    private:
        SDL_Window* pWindow;
        std::shared_ptr<VulkanInstance> instance;
        std::unique_ptr<VulkanPhysicalDevice> physicalDevice;
        std::unique_ptr<VulkanQueue> graphicsQueue;
        std::unique_ptr<VulkanDevice> device;
        std::unique_ptr<VulkanSurface> surface;

        #ifdef _DEBUG
            std::unique_ptr<VulkanDebuger> debugMessenger;
        #endif
    };
}