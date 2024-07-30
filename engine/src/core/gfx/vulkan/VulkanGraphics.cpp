#include "VulkanGraphics.h"
#include <iostream>
#include <memory>

namespace Hydro::gfx
{
    VulkanGraphics::VulkanGraphics( app::Window& window )
    {
        pWindow = window.GetWindow();
        instance = std::make_shared<VulkanInstance>(pWindow);
        physicalDevice = std::make_unique<VulkanPhysicalDevice>(instance->GetInstance());
        device = std::make_unique<VulkanDevice>(*physicalDevice);
        graphicsQueue = std::make_unique<VulkanQueue>(*device, 0);
        surface = std::make_unique<VulkanSurface>(instance, pWindow);

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