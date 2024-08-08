#pragma once
#include <vulkan/vulkan.h>
#include <memory>
#include "VulkanDevice.h"
#include <vector>
#include "VulkanSwapChain.h"
#include "VulkanRenderPass.h"

namespace Hydro::gfx
{
    class VulkanFramebuffer
    {
    public:
        VulkanFramebuffer( std::shared_ptr<VulkanDevice> device, VulkanSwapChain& swapChain, VulkanRenderPass& renderPass );
        ~VulkanFramebuffer();
        const std::vector<VkFramebuffer>& GetFramebuffer() const; //Maybe can´t be const
    private:
        std::shared_ptr<VulkanDevice> device;
        std::vector<VkFramebuffer> framebuffers;
    };
}