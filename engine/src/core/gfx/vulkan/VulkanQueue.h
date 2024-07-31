#pragma once
#include <vulkan/vulkan.h>
#include <optional>

namespace Hydro::gfx
{
    class VulkanDevice;

    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    QueueFamilyIndices FindQueueFamilies( VkPhysicalDevice device, VkSurfaceKHR surface );

    class VulkanQueue
    {
    public:
        VulkanQueue( VulkanDevice& device, uint32_t queueIndex, uint32_t queueType );
        VkQueue GetQueue() const;
    private:
        VkQueue queue;
    };
}