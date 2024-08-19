#include "VulkanQueue.h"
#include <vector>
#include "VulkanDevice.h"

namespace Hydro::gfx
{
    VulkanQueue::VulkanQueue( VulkanDevice& device, uint32_t queueIndex, uint32_t queueType )
    {
        //TODO: This system is not final but i need more information on how the queues are used in the API before improving it

        switch ( queueType )
        {
        case 0:
            vkGetDeviceQueue( device.GetDevice(), device.GetQueueFamilyIndex().graphicsFamily.value(), queueIndex, &queue );
            break;
        case 1:
            vkGetDeviceQueue( device.GetDevice(), device.GetQueueFamilyIndex().presentFamily.value(), queueIndex, &queue );
            break;
        default:
            break;
        }

        
    }

    VkQueue VulkanQueue::GetQueue() const
    {
        return queue;
    }

    QueueFamilyIndices FindQueueFamilies( VkPhysicalDevice device, VkSurfaceKHR surface )
    {
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for( const auto& queueFamily : queueFamilies )
        {
            if( queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT )
            {
                indices.graphicsFamily = i;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

            if( presentSupport )
            {
                indices.presentFamily = i;
            }

            if( indices.isComplete() )
            {
                break;
            }

            i++;
        }

        return indices;
    }
}