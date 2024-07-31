#include "VulkanDevice.h"
#include "VulkanDebuger.h"
#include <stdexcept>
#include <vector>
#include <set>


namespace Hydro::gfx
{
    VulkanDevice::VulkanDevice( VulkanPhysicalDevice& physicalDevice )
    {
        queueFamilyIndices = physicalDevice.FindQueueFamilies();
        
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = { queueFamilyIndices.graphicsFamily.value(), queueFamilyIndices.presentFamily.value() };

        float queuePriority = 1.0f;
        for( uint32_t queueFamilyIndex : uniqueQueueFamilies )
        {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
            queueCreateInfo.queueCount = 1;

            queueCreateInfo.pQueuePriorities = &queuePriority;

            queueCreateInfos.push_back( queueCreateInfo );
        }

        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.pEnabledFeatures = &deviceFeatures;

        auto deviceExtensions = VulkanPhysicalDevice::GetDeviceExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = deviceExtensions.data();
        
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

    QueueFamilyIndices VulkanDevice::GetQueueFamilyIndex() const
    {
        return queueFamilyIndices;
    }
}