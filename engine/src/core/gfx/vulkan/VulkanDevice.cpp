#include "VulkanDevice.h"
#include "VulkanDebuger.h"
#include <stdexcept>

namespace Hydro::gfx
{
    VulkanDevice::VulkanDevice( VulkanPhysicalDevice& physicalDevice )
    {
        QueueFamilyIndices indices = physicalDevice.FindQueueFamilies();
        
        queueFamilyIndex = indices.graphicsFamily.value();

        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
        queueCreateInfo.queueCount = 1;

        float queuePriority = 1.0f;
        queueCreateInfo.pQueuePriorities = &queuePriority;

        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.pQueueCreateInfos = &queueCreateInfo;
        createInfo.queueCreateInfoCount = 1;
        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledExtensionCount = 0;
        
        #ifdef _DEBUG
            auto validationLayers = VulkanDebuger::GetValidationLayers();
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        #else
            createInfo.enabledLayerCount = 0;
        #endif

        if( vkCreateDevice( physicalDevice.GetPhysicalDevice(), &createInfo, nullptr, &device ) != VK_SUCCESS )
        {
            throw std::runtime_error("Failed to create logical device!");
        }
    }

    VulkanDevice::~VulkanDevice()
    {
        vkDestroyDevice( device, nullptr );
    }

    VkDevice VulkanDevice::GetDevice() const
    {
        return device;
    }

    uint32_t VulkanDevice::GetQueueFamilyIndex() const
    {
        return queueFamilyIndex;
    }
}