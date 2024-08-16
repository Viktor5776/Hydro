#pragma once
#include <vulkan/vulkan.h>
#include <memory>
#include "VulkanDevice.h"
#include "VulkanPhysicalDevice.h"

namespace Hydro::gfx
{
    class VulkanBuffer
    {
    public:
        VulkanBuffer( VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, 
            std::shared_ptr<VulkanDevice> device, VulkanPhysicalDevice physicalDevice );
        ~VulkanBuffer();
        VkBuffer& GetBuffer();
        VkDeviceMemory& GetBufferMemory();
        static uint32_t FindMemoryType( VulkanPhysicalDevice& physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);
        static void CopyBuffer( VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue );
    protected:
        std::shared_ptr<VulkanDevice> device;
        VkBuffer buffer;
        VkDeviceMemory bufferMemory;
    };
}