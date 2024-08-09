#pragma once
#include <vulkan/vulkan.h>
#include <memory>
#include "VulkanDevice.h"
#include "VulkanCommandPool.h"
#include "VulkanRenderPass.h"
#include "VulkanSwapChain.h"
#include "VulkanFramebuffer.h"
#include "VulkanGraphicsPipeline.h"

namespace Hydro::gfx
{
    class VulkanCommandBuffer
    {
    public:
        VulkanCommandBuffer(std::shared_ptr<VulkanDevice> device, VulkanCommandPool& commandPool);
        void RecordCommandBuffer( VulkanRenderPass& renderPass, VulkanFramebuffer& frameBuffer, 
            VulkanSwapChain& swapChain, VulkanGraphicsPipeline& graphicsPipeline, uint32_t imageIndex );
    private:
        std::shared_ptr<VulkanDevice> device;
        VkCommandBuffer commandBuffer;
    };
}