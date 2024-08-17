#include "VulkanUniformBuffer.h"
#include <stdexcept>

namespace Hydro::gfx
{
    VulkanUniformBuffer::VulkanUniformBuffer( std::shared_ptr<VulkanDevice> device, VulkanPhysicalDevice& physicalDevice, const uint16_t maxFramesInFlight )
        : device(device)
    {
        VkDescriptorSetLayoutBinding uboLayoutBinding = {};
        uboLayoutBinding.binding = 0;
        uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        uboLayoutBinding.descriptorCount = 1;
        uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
        uboLayoutBinding.pImmutableSamplers = nullptr;

        VkDescriptorSetLayoutCreateInfo layoutInfo = {};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = 1;
        layoutInfo.pBindings = &uboLayoutBinding;

        if (vkCreateDescriptorSetLayout(device->GetDevice(), &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create descriptor set layout!");
        }

        VkDeviceSize bufferSize = sizeof(BufferData);

        uniformBuffers.reserve(maxFramesInFlight);
        uniformBuffersMapped.resize(maxFramesInFlight);

        for( size_t i = 0; i < maxFramesInFlight; i++ )
        {
            uniformBuffers.emplace_back( 
                bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, 
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, 
                device, physicalDevice );
            
            
            vkMapMemory(device->GetDevice(), uniformBuffers[i].GetBufferMemory(), 0, bufferSize, 0, &uniformBuffersMapped[i]);
        }

        VkDescriptorPoolSize poolSize = {};
        poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        poolSize.descriptorCount = static_cast<uint32_t>(maxFramesInFlight);

        VkDescriptorPoolCreateInfo poolInfo = {};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = 1;
        poolInfo.pPoolSizes = &poolSize;
        poolInfo.maxSets = maxFramesInFlight;

        if( vkCreateDescriptorPool(device->GetDevice(), &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS )
        {
            throw std::runtime_error("Failed to create descriptor pool!");
        }

        std::vector<VkDescriptorSetLayout> layouts(maxFramesInFlight, descriptorSetLayout);

        VkDescriptorSetAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = descriptorPool;
        allocInfo.descriptorSetCount = static_cast<uint32_t>(maxFramesInFlight);
        allocInfo.pSetLayouts = layouts.data();

        descriptorSets.resize(maxFramesInFlight);
        if( vkAllocateDescriptorSets(device->GetDevice(), &allocInfo, descriptorSets.data()) != VK_SUCCESS )
        {
            throw std::runtime_error("Failed to allocate descriptor sets!");
        }

        for( size_t i = 0; i < maxFramesInFlight; i++ )
        {
            VkDescriptorBufferInfo bufferInfo = {};
            bufferInfo.buffer = uniformBuffers[i].GetBuffer();
            bufferInfo.offset = 0;
            bufferInfo.range = sizeof(BufferData);

            VkWriteDescriptorSet descriptorWrite = {};
            descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrite.dstSet = descriptorSets[i];
            descriptorWrite.dstBinding = 0;
            descriptorWrite.dstArrayElement = 0;
            descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            descriptorWrite.descriptorCount = 1;
            descriptorWrite.pBufferInfo = &bufferInfo;
            descriptorWrite.pImageInfo = nullptr; 
            descriptorWrite.pTexelBufferView = nullptr; 

            vkUpdateDescriptorSets(device->GetDevice(), 1, &descriptorWrite, 0, nullptr);
        }
    }

    VulkanUniformBuffer::~VulkanUniformBuffer()
    {
        vkDestroyDescriptorPool(device->GetDevice(), descriptorPool, nullptr);
        vkDestroyDescriptorSetLayout(device->GetDevice(), descriptorSetLayout, nullptr);
    }

    VkDescriptorSetLayout& VulkanUniformBuffer::GetDescriptorSetLayout()
    {
        return descriptorSetLayout;
    }

    std::vector<VkDescriptorSet>& VulkanUniformBuffer::GetDescriptorSets()
    {
        return descriptorSets;
    }

    void VulkanUniformBuffer::UpdateUniformBuffer( const uint16_t currentImage, BufferData data )
    {
        memcpy(uniformBuffersMapped[currentImage], &data, sizeof(data));
    }
}