#include "VulkanVertexBuffer.h"
#include <stdexcept>

namespace Hydro::gfx
{
    VulkanVertexBuffer::VulkanVertexBuffer( std::shared_ptr<VulkanDevice> device, VulkanPhysicalDevice& physicalDevice )
        :
        device( device )
    {
        VkBufferCreateInfo bufferInfo = {};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = sizeof(vertices[0]) * vertices.size();   
        bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if( vkCreateBuffer( device->GetDevice(), &bufferInfo, nullptr, &vertexBuffer ) != VK_SUCCESS )
        {
            throw std::runtime_error("Failed to create vertex buffer");
        }

        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements( device->GetDevice(), vertexBuffer, &memRequirements );

        VkMemoryAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = findMemoryType( physicalDevice, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT );
    
        if( vkAllocateMemory( device->GetDevice(), &allocInfo, nullptr, &vertexBufferMemory ) != VK_SUCCESS )
        {
            throw std::runtime_error("Failed to allocate vertex buffer memory");
        }

        vkBindBufferMemory( device->GetDevice(), vertexBuffer, vertexBufferMemory, 0 );

        void* data;
        vkMapMemory( device->GetDevice(), vertexBufferMemory, 0, bufferInfo.size, 0, &data );
        memcpy( data, vertices.data(), (size_t) bufferInfo.size );
        vkUnmapMemory( device->GetDevice(), vertexBufferMemory );
    }

    VulkanVertexBuffer::~VulkanVertexBuffer()
    {
        vkDestroyBuffer( device->GetDevice(), vertexBuffer, nullptr );
        vkFreeMemory( device->GetDevice(), vertexBufferMemory, nullptr );
    }

    VkBuffer& VulkanVertexBuffer::GetVertexBuffer()
    {
        return vertexBuffer;
    }

    VkDeviceMemory& VulkanVertexBuffer::GetVertexBufferMemory()
    {
        return vertexBufferMemory;
    }

    size_t VulkanVertexBuffer::GetBufferSize()
    {
        return vertices.size();
    }

    uint32_t VulkanVertexBuffer::findMemoryType( VulkanPhysicalDevice& physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties )
    {
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties( physicalDevice.GetPhysicalDevice(), &memProperties );

        for( uint32_t i = 0; i < memProperties.memoryTypeCount; i++ )
        {
            if( typeFilter & ( 1 << i ) && ( memProperties.memoryTypes[i].propertyFlags & properties ) == properties )
            {
                return i;
            }
        }

        throw std::runtime_error("Failed to find suitable memory type");
    }
}