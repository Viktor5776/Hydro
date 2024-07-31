#pragma once
#include <vulkan/vulkan.h>
#include "VulkanPhysicalDevice.h"

namespace Hydro::gfx
{
    class VulkanDevice
    {
    public:
        VulkanDevice( VulkanPhysicalDevice& physicalDevice );
        ~VulkanDevice();
        VkDevice GetDevice() const;
        QueueFamilyIndices GetQueueFamilyIndex() const;
    private:
        VkDevice device;
        QueueFamilyIndices queueFamilyIndices;
    };
}