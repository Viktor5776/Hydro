#include "VulkanGraphics.h"
#include <iostream>
#include <vulkan/vulkan.h>

namespace Hydro::gfx
{
    VulkanGraphics::VulkanGraphics()
    {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::cout << extensionCount << " extensions supported\n";
    }

    VulkanGraphics::~VulkanGraphics()
    {
    }

    void VulkanGraphics::Render()
    {
    }
}