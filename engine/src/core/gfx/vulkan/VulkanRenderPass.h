#pragma once
#include <vulkan/vulkan.h>
#include <memory>
#include "VulkanDevice.h"

namespace Hydro::gfx
{
    class VulkanRenderPass
    {
    public:
        VulkanRenderPass( std::shared_ptr<VulkanDevice> device, VkFormat swapChainImageFormat );
        ~VulkanRenderPass();
        VkRenderPass GetRenderPass() const;
    private:
        std::shared_ptr<VulkanDevice> device;
        VkRenderPass renderPass;
    };
}