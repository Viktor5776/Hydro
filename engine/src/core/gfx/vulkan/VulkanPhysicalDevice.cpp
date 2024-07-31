#include "VulkanPhysicalDevice.h"
#include <vector>
#include <stdexcept>

namespace Hydro::gfx
{
    VulkanPhysicalDevice::VulkanPhysicalDevice( VkInstance instance, VkSurfaceKHR surface )
        :
        surface( surface )
    {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices( instance, &deviceCount, nullptr );

        if( deviceCount == 0 )
        {
            throw std::runtime_error("Failed to find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices( deviceCount );
        vkEnumeratePhysicalDevices( instance, &deviceCount, devices.data() );

        for( const auto& device : devices )
        {
            //NOTE: May want to use a score system to determine the best device
            if( IsDeviceSuitable( device ) )
            {
                physicalDevice = device;
                break;
            }
        }

        if( physicalDevice == VK_NULL_HANDLE )
        {
            throw std::runtime_error("Failed to find a suitable GPU!");
        }
    }

    VkPhysicalDevice VulkanPhysicalDevice::GetPhysicalDevice() const
    { 
        return physicalDevice; 
    }

    bool VulkanPhysicalDevice::IsDeviceSuitable( VkPhysicalDevice device )
    {
        //NOTE: May want to use a score system to determine the best device
        QueueFamilyIndices indices = Hydro::gfx::FindQueueFamilies(device, surface);

        return indices.isComplete();
    }

    QueueFamilyIndices VulkanPhysicalDevice::FindQueueFamilies()
    {
        return Hydro::gfx::FindQueueFamilies( physicalDevice, surface );
    }

    
}