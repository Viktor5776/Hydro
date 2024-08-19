#include "VulkanBuffer.h"
#include <stdexcept>

namespace Hydro::gfx
{
    VulkanBuffer::VulkanBuffer( VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, 
        std::shared_ptr<VulkanDevice> device, VulkanPhysicalDevice physicalDevice )
        : device( device )
    {
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if( vkCreateBuffer( device->GetDevice(), &bufferInfo, nullptr, &buffer ) != VK_SUCCESS )
        {
            throw std::runtime_error( "Failed to create buffer!" );
        }

        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements( device->GetDevice(), buffer, &memRequirements );

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = FindMemoryType( physicalDevice, memRequirements.memoryTypeBits, properties );

        if( vkAllocateMemory( device->GetDevice(), &allocInfo, nullptr, &bufferMemory ) != VK_SUCCESS )
        {
            throw std::runtime_error( "Failed to allocate buffer memory!" );
        }

        vkBindBufferMemory( device->GetDevice(), buffer, bufferMemory, 0 );
    }

    VulkanBuffer::~VulkanBuffer()
    {
        vkDestroyBuffer( device->GetDevice(), buffer, nullptr );
        vkFreeMemory( device->GetDevice(), bufferMemory, nullptr );
    }

    VkBuffer& VulkanBuffer::GetBuffer()
    {
        return buffer;
    }

    VkDeviceMemory& VulkanBuffer::GetBufferMemory()
    {
        return bufferMemory;
    }

    uint32_t VulkanBuffer::FindMemoryType( VulkanPhysicalDevice& physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties )
    {
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties( physicalDevice.GetPhysicalDevice(), &memProperties );

        for( uint32_t i = 0; i < memProperties.memoryTypeCount; i++ )
        {
            if( ( typeFilter & ( 1 << i ) ) && ( memProperties.memoryTypes[i].propertyFlags & properties ) == properties )
            {
                return i;
            }
        }

        throw std::runtime_error( "Failed to find suitable memory type!" );
    }

    void VulkanBuffer::CopyBuffer( VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue )
    {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = commandPool;
        allocInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer;
        vkAllocateCommandBuffers( device, &allocInfo, &commandBuffer );

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer( commandBuffer, &beginInfo );

        VkBufferCopy copyRegion{};
        copyRegion.srcOffset = 0;
        copyRegion.dstOffset = 0;
        copyRegion.size = size;
        vkCmdCopyBuffer( commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion );

        vkEndCommandBuffer( commandBuffer );

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        vkQueueSubmit( graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE );
        vkQueueWaitIdle( graphicsQueue );

        vkFreeCommandBuffers( device, commandPool, 1, &commandBuffer );
    }
}