#include "VulkanIndexBuffer.h"
#include <stdexcept>

namespace Hydro::gfx
{
    VulkanIndexBuffer::VulkanIndexBuffer( std::shared_ptr<VulkanDevice> device, VulkanPhysicalDevice& physicalDevice, 
            VkCommandPool commandPool, VkQueue graphicsQueue, std::vector<uint32_t> indices )
        : 
        VulkanBuffer(
            static_cast<VkDeviceSize>(sizeof(indices[0]) * indices.size()),
            VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
            device, physicalDevice ),
        bufferSize(indices.size())
    {
        VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

        VulkanBuffer stagingBuffer( bufferSize,
            VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            device, physicalDevice );
        
        void* data;
        vkMapMemory(device->GetDevice(), stagingBuffer.GetBufferMemory(), 0, bufferSize, 0, &data);
        memcpy(data, indices.data(), (size_t)bufferSize);
        vkUnmapMemory(device->GetDevice(), stagingBuffer.GetBufferMemory());

        CopyBuffer(stagingBuffer.GetBuffer(), buffer, bufferSize, device->GetDevice(), commandPool, graphicsQueue);
    }

    size_t VulkanIndexBuffer::GetBufferSize()
    {
        return bufferSize;
    }
}