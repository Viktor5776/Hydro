#pragma once
#include "../IGraphics.h"
#include <vulkan/vulkan.h>
#include <SDL2/SDL.h>
#include <memory>
#include "VulkanDebuger.h"
#include "VulkanInstance.h"

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

        #ifdef _DEBUG
            std::unique_ptr<VulkanDebuger> debugMessenger;
        #endif
        std::shared_ptr<VulkanInstance> instance;
    };
}