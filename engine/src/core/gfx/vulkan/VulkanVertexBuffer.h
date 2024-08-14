#pragma once
#include <vulkan/vulkan.h>
#include "VulkanVertex.h"
#include <memory>
#include <vector>
#include "VulkanDevice.h"
#include "VulkanPhysicalDevice.h"

namespace Hydro::gfx
{
    class VulkanVertexBuffer
    {
    public:
        VulkanVertexBuffer( std::shared_ptr<VulkanDevice> device, VulkanPhysicalDevice& physicalDevice );
        ~VulkanVertexBuffer();
        VkBuffer& GetVertexBuffer();
        VkDeviceMemory& GetVertexBufferMemory();
        size_t GetBufferSize();
        static uint32_t findMemoryType( VulkanPhysicalDevice& physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);
    private:
        std::shared_ptr<VulkanDevice> device;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;

        std::vector<VulkanVertex> vertices = {
            {{-1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}},
            {{1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
            {{-1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
            {{1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
            {{1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
            {{-1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}
        };
    };
}