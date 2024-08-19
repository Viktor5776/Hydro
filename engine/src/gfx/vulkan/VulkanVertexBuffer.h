#pragma once
#include <vulkan/vulkan.h>
#include <memory>
#include <vector>
#include "VulkanVertex.h"
#include "VulkanBuffer.h"

namespace Hydro::gfx
{
    class VulkanVertexBuffer : public VulkanBuffer
    {
    public:
        VulkanVertexBuffer( std::shared_ptr<VulkanDevice> device, VulkanPhysicalDevice& physicalDevice, 
            VkCommandPool commandPool, VkQueue graphicsQueue, std::vector<VulkanVertex> vertices );
        size_t GetBufferSize();
    private:
        size_t bufferSize;
        //TODO: Better soulution for getting vertices pass them in as a parameter maybe?
        //std::vector<VulkanVertex> vertices = {
        //    {{-1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}},
        //    {{1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
        //    {{-1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
        //    {{1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
        //    {{1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
        //    {{-1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}
        //};
    };
}