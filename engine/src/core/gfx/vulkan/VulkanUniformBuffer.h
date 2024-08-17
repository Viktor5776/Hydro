#pragma once
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "VulkanDevice.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanBuffer.h"

namespace Hydro::gfx
{
    class VulkanUniformBuffer
    {
    public:
        struct BufferData
        {
            alignas(16) glm::mat4 model;
            alignas(16) glm::mat4 view;
            alignas(16) glm::mat4 proj;
        };
    public:
        VulkanUniformBuffer( std::shared_ptr<VulkanDevice> device, VulkanPhysicalDevice& physicalDevice, uint16_t maxFramesInFlight );
        ~VulkanUniformBuffer();
        VkDescriptorSetLayout& GetDescriptorSetLayout();
        std::vector<VkDescriptorSet>& GetDescriptorSets();
        void UpdateUniformBuffer( uint16_t currentImage, BufferData data );
    private:
        std::shared_ptr<VulkanDevice> device;
        VkDescriptorSetLayout descriptorSetLayout;
        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;
        std::vector<VulkanBuffer> uniformBuffers;
        std::vector<void*> uniformBuffersMapped;
    };
}