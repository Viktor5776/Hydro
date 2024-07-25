#include "VulkanGraphics.h"
#include <iostream>
#include <memory>

namespace Hydro::gfx
{
    VulkanGraphics::VulkanGraphics( app::Window& window )
    {
        pWindow = window.GetWindow();
        instance = std::make_shared<VulkanInstance>(pWindow);

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