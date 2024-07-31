#pragma once
#include <vulkan/vulkan.h>
#include "VulkanQueue.h"

namespace Hydro::gfx
{

    class VulkanPhysicalDevice
    {
    public:
        VulkanPhysicalDevice( VkInstance instance, VkSurfaceKHR surface );
        VkPhysicalDevice GetPhysicalDevice() const;
        QueueFamilyIndices FindQueueFamilies();
    private:
        bool IsDeviceSuitable( VkPhysicalDevice device );
    private:
        VkSurfaceKHR surface = VK_NULL_HANDLE;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    };
}