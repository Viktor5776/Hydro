#pragma once
#include <vulkan/vulkan.h>
#include <memory>
#include "VulkanDevice.h"

namespace Hydro::gfx
{
    class VulkanGraphicsPipeline
    {
    public:
        VulkanGraphicsPipeline( std::shared_ptr<VulkanDevice> device );
        ~VulkanGraphicsPipeline();
    private:
        std::shared_ptr<VulkanDevice> device;
    };
}