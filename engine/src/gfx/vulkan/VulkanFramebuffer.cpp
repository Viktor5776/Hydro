#include "VulkanFramebuffer.h"
#include <stdexcept>

namespace Hydro::gfx
{
    VulkanFramebuffer::VulkanFramebuffer( std::shared_ptr<VulkanDevice> device, VulkanSwapChain& swapChain, VulkanRenderPass& renderPass )
        : 
        device( device )
    {
        framebuffers.resize(swapChain.GetSwapChainImageViews().size());
        for (size_t i = 0; i < swapChain.GetSwapChainImageViews().size(); i++) 
        {
            VkImageView attachments[] = {
                swapChain.GetSwapChainImageViews()[i]
            };

            VkFramebufferCreateInfo framebufferInfo{};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = renderPass.GetRenderPass();
            framebufferInfo.attachmentCount = 1;
            framebufferInfo.pAttachments = attachments;
            framebufferInfo.width = swapChain.GetSwapChainExtent().width;
            framebufferInfo.height = swapChain.GetSwapChainExtent().height;
            framebufferInfo.layers = 1;

            if (vkCreateFramebuffer(device->GetDevice(), &framebufferInfo, nullptr, &framebuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create framebuffer!");
            }
        }
    }

    VulkanFramebuffer::~VulkanFramebuffer()
    {
        for (auto framebuffer : framebuffers) {
            vkDestroyFramebuffer(device->GetDevice(), framebuffer, nullptr);
        }
    }

    const std::vector<VkFramebuffer>& VulkanFramebuffer::GetFramebuffer() const
    {
        return framebuffers;
    }
}