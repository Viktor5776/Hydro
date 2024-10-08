#pragma once
#include <vulkan/vulkan.h>
#include <memory>
#include "VulkanDevice.h"
#include "VulkanSwapChain.h"
#include "VulkanRenderPass.h"
#include "VulkanUniformBuffer.h"

namespace Hydro::gfx
{
    class VulkanGraphicsPipeline
    {
    public:
        VulkanGraphicsPipeline( std::shared_ptr<VulkanDevice> device, VulkanSwapChain& swapChain, VulkanRenderPass& renderPass, VulkanUniformBuffer& uniformBuffer );
        ~VulkanGraphicsPipeline();
        VkPipeline GetGraphicsPipeline() const;
        VkPipelineLayout GetPipelineLayout() const;
    private:
        std::shared_ptr<VulkanDevice> device;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;
    };
}