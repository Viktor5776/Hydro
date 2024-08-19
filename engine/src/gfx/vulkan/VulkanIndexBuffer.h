#pragma once
#include "VulkanBuffer.h"

namespace Hydro::gfx
{
    class VulkanIndexBuffer : public VulkanBuffer
    {
    public:
        VulkanIndexBuffer( std::shared_ptr<VulkanDevice> device, VulkanPhysicalDevice& physicalDevice, 
            VkCommandPool commandPool, VkQueue graphicsQueue, std::vector<uint32_t> indices );
        size_t GetBufferSize();
    private:
        size_t bufferSize;
    };
}