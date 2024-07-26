#pragma once
#include <vulkan/vulkan.h>


#include <optional>

namespace Hydro::gfx
{
    //NOTE: Queue shold probebly have its own file/class
    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;

        bool isComplete() {
            return graphicsFamily.has_value();
        }
    };

    class VulkanPhysicalDevice
    {
    public:
        VulkanPhysicalDevice( VkInstance instance );
        VkPhysicalDevice GetPhysicalDevice() const;
    private:
        bool IsDeviceSuitable( VkPhysicalDevice device );
        QueueFamilyIndices FindQueueFamilies( VkPhysicalDevice device );
    private:
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    };
}