#include "VulkanPhysicalDevice.h"
#include <stdexcept>
#include <set>
#include "VulkanSwapChain.h"

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

    const std::vector<const char*> VulkanPhysicalDevice::GetDeviceExtensions()
    {
        return { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
    }

    bool VulkanPhysicalDevice::IsDeviceSuitable( VkPhysicalDevice device )
    {
        //NOTE: May want to use a score system to determine the best device
        QueueFamilyIndices indices = Hydro::gfx::FindQueueFamilies(device, surface);

        bool extensionsSupported = CheckDeviceExtensionSupport(device);

        bool swapChainAdequate = false;
        if( extensionsSupported )
        {
            SwapChainSupportDetails swapChainSupport = Hydro::gfx::QuerySwapChainSupport(device, surface);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        return indices.isComplete() && extensionsSupported && swapChainAdequate;
    }

    bool VulkanPhysicalDevice::CheckDeviceExtensionSupport( VkPhysicalDevice device )
    {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties( device, nullptr, &extensionCount, nullptr );

        std::vector<VkExtensionProperties> availableExtensions( extensionCount );
        vkEnumerateDeviceExtensionProperties( device, nullptr, &extensionCount, availableExtensions.data() );

        auto requiredExtensions = GetDeviceExtensions();
        std::set<std::string> requiredExtensionsSet( requiredExtensions.begin(), requiredExtensions.end() );

        for( const auto& extension : availableExtensions )
        {
            requiredExtensionsSet.erase( extension.extensionName );
        }

        return requiredExtensionsSet.empty();
    }

    QueueFamilyIndices VulkanPhysicalDevice::FindQueueFamilies()
    {
        return Hydro::gfx::FindQueueFamilies( physicalDevice, surface );
    }

    
}