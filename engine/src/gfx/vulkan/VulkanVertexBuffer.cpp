#include "VulkanVertexBuffer.h"
#include <stdexcept>

namespace Hydro::gfx
{
    VulkanVertexBuffer::VulkanVertexBuffer( std::shared_ptr<VulkanDevice> device, VulkanPhysicalDevice& physicalDevice, 
        VkCommandPool commandPool, VkQueue graphicsQueue, std::vector<VulkanVertex> vertices )
        : 
        VulkanBuffer( 
            static_cast<VkDeviceSize>(sizeof(vertices[0]) * vertices.size()), 
            VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, 
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, 
            device, physicalDevice ),
        bufferSize( vertices.size() )
    {
        VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

        VulkanBuffer stagingBuffer( bufferSize, 
            VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, 
            device, physicalDevice );

        void* data;
        vkMapMemory( device->GetDevice(), stagingBuffer.GetBufferMemory(), 0, bufferSize, 0, &data );
        memcpy( data, vertices.data(), (size_t)bufferSize );
        vkUnmapMemory( device->GetDevice(), stagingBuffer.GetBufferMemory() );

        CopyBuffer( stagingBuffer.GetBuffer(), buffer, bufferSize, device->GetDevice(), commandPool, graphicsQueue );
    }

    size_t VulkanVertexBuffer::GetBufferSize()
    {
        return bufferSize;
    }
}