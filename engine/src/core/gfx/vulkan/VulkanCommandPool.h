#pragma once
#include <vulkan/vulkan.h>
#include <memory>
#include "VulkanDevice.h"

namespace Hydro::gfx
{
    class VulkanCommandPool
    {
    public:
        VulkanCommandPool(std::shared_ptr<VulkanDevice> device, VulkanPhysicalDevice& physicalDevice);
        ~VulkanCommandPool();
        VkCommandPool GetCommandPool() const;
    private:
        std::shared_ptr<VulkanDevice> device;
        VkCommandPool commandPool;
    };
}