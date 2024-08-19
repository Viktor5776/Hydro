#include "VulkanCommandPool.h"
#include "VulkanDevice.h"
#include <stdexcept>

namespace Hydro::gfx
{
    VulkanCommandPool::VulkanCommandPool(std::shared_ptr<VulkanDevice> device, VulkanPhysicalDevice& physicalDevice)
        : 
        device(device)
    {
        VkCommandPoolCreateInfo poolInfo = {};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.queueFamilyIndex = physicalDevice.FindQueueFamilies().graphicsFamily.value();
        poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

        if (vkCreateCommandPool(device->GetDevice(), &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create command pool!");
        }
    }

    VulkanCommandPool::~VulkanCommandPool()
    {
        vkDestroyCommandPool(device->GetDevice(), commandPool, nullptr);
    }

    VkCommandPool VulkanCommandPool::GetCommandPool() const
    {
        return commandPool;
    }
}