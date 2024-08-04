#include "VulkanGraphics.h"
#include <iostream>
#include <memory>

namespace Hydro::gfx
{
    VulkanGraphics::VulkanGraphics( app::Window& window )
    {
        pWindow = window.GetWindow();
        instance = std::make_shared<VulkanInstance>(pWindow);
        surface = std::make_unique<VulkanSurface>(instance, pWindow);
        physicalDevice = std::make_unique<VulkanPhysicalDevice>(instance->GetInstance(), surface->GetSurface());
        device = std::make_shared<VulkanDevice>(*physicalDevice);
        graphicsQueue = std::make_unique<VulkanQueue>(*device, 0, 0);
        presentQueue = std::make_unique<VulkanQueue>(*device, 0, 1);
        swapChain = std::make_unique<VulkanSwapChain>(device, *physicalDevice, *surface, pWindow);
        graphicsPipeline = std::make_unique<VulkanGraphicsPipeline>(device);

        #ifdef _DEBUG
            debugMessenger = std::make_unique<VulkanDebuger>(instance);
        #endif
    }

    VulkanGraphics::~VulkanGraphics()
    {
        std::cout << "VulkanGraphics destructor called!" << std::endl;
    }

    void VulkanGraphics::Render()
    {
        
    }
}