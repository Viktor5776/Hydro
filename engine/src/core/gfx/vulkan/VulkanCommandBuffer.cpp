#include "VulkanCommandBuffer.h"
#include <stdexcept>

namespace Hydro::gfx
{
    VulkanCommandBuffer::VulkanCommandBuffer(std::shared_ptr<VulkanDevice> device, VulkanCommandPool& commandPool, uint32_t commandBufferCount)
        : 
        device(device)
    {
        commandBuffers.resize( commandBufferCount );

        VkCommandBufferAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool.GetCommandPool();
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = commandBufferCount;

        if (vkAllocateCommandBuffers(device->GetDevice(), &allocInfo, commandBuffers.data()) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to allocate command buffers!");
        }
    }

    void VulkanCommandBuffer::RecordCommandBuffer( VulkanRenderPass& renderPass, VulkanFramebuffer& framebuffer, 
        VulkanSwapChain& swapChain, VulkanGraphicsPipeline& graphicsPipeline, VulkanVertexBuffer& vertexBuffer, 
        VulkanIndexBuffer& indexBuffer, VulkanUniformBuffer& uniformBuffer,uint32_t imageIndex, uint32_t commandBufferIndex )
    {
        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = 0;
        beginInfo.pInheritanceInfo = nullptr;

        if (vkBeginCommandBuffer(commandBuffers[commandBufferIndex], &beginInfo) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to begin recording command buffer!");
        }

        VkRenderPassBeginInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = renderPass.GetRenderPass();
        renderPassInfo.framebuffer = framebuffer.GetFramebuffer()[imageIndex];
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = swapChain.GetSwapChainExtent();

        VkClearValue clearColor = { { {0.0f, 0.0f, 0.0f, 1.0f} } };
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(commandBuffers[commandBufferIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBuffers[commandBufferIndex], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline.GetGraphicsPipeline() );

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = static_cast<float>(swapChain.GetSwapChainExtent().width);
        viewport.height = static_cast<float>(swapChain.GetSwapChainExtent().height);
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        vkCmdSetViewport(commandBuffers[commandBufferIndex], 0, 1, &viewport);

        VkRect2D scissor{};
        scissor.offset = {0, 0};
        scissor.extent = swapChain.GetSwapChainExtent();
        vkCmdSetScissor(commandBuffers[commandBufferIndex], 0, 1, &scissor);

        VkBuffer vertexBuffers[] = { vertexBuffer.GetBuffer() };
        VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(commandBuffers[commandBufferIndex], 0, 1, vertexBuffers, offsets);

        vkCmdBindIndexBuffer(commandBuffers[commandBufferIndex], indexBuffer.GetBuffer(), 0, VK_INDEX_TYPE_UINT32);

        vkCmdBindDescriptorSets(commandBuffers[commandBufferIndex], VK_PIPELINE_BIND_POINT_GRAPHICS, 
            graphicsPipeline.GetPipelineLayout(), 0, 1, &uniformBuffer.GetDescriptorSets()[commandBufferIndex], 0, nullptr);
            
        vkCmdDrawIndexed(commandBuffers[commandBufferIndex], static_cast<uint32_t>(indexBuffer.GetBufferSize()), 1, 0, 0, 0);

        vkCmdEndRenderPass(commandBuffers[commandBufferIndex]);

        if (vkEndCommandBuffer(commandBuffers[commandBufferIndex]) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to record command buffer!");
        }
    }

    std::vector<VkCommandBuffer>& VulkanCommandBuffer::GetCommandBuffers()
    {
        return commandBuffers;
    }
}