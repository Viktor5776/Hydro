#pragma once
#include <vulkan/vulkan.h>
#include <VulkanPhysicalDevice.h>

namespace Hydro::gfx
{
    class VulkanDevice
    {
    public:
        VulkanDevice( VulkanPhysicalDevice& physicalDevice );
        ~VulkanDevice();
        VkDevice GetDevice() const;
        uint32_t GetQueueFamilyIndex() const;
    private:
        VkDevice device;
        uint32_t queueFamilyIndex;
    };
}