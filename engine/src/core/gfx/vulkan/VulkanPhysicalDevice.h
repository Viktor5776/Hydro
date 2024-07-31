#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "VulkanQueue.h"

namespace Hydro::gfx
{

    class VulkanPhysicalDevice
    {
    public:
        VulkanPhysicalDevice( VkInstance instance, VkSurfaceKHR surface );
        VkPhysicalDevice GetPhysicalDevice() const;
        QueueFamilyIndices FindQueueFamilies();
        static const std::vector<const char*> GetDeviceExtensions();
    private:
        bool IsDeviceSuitable( VkPhysicalDevice device );
        bool CheckDeviceExtensionSupport( VkPhysicalDevice device );
    private:
        VkSurfaceKHR surface = VK_NULL_HANDLE;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    };
}