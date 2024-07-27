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
        device = std::make_unique<VulkanDevice>(physicalDevice.get());
        graphicsQueue = std::make_unique<VulkanQueue>(device, 0);


        #ifdef _DEBUG
            debugMessenger = std::make_unique<VulkanDebuger>(instance);
        #endif
    }

    VulkanGraphics::~VulkanGraphics()
    {
        
    }

    void VulkanGraphics::Render()
    {
        
    }
}