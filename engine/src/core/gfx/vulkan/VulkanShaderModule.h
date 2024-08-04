#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <memory>
#include "VulkanDevice.h"

namespace Hydro::gfx
{
    class VulkanShaderModule
    {
    public:
        VulkanShaderModule( std::shared_ptr<VulkanDevice> deivce, const std::string& filename );
        ~VulkanShaderModule();
        VkShaderModule GetShaderModule() const;
    private:
        std::shared_ptr<VulkanDevice> device;
        VkShaderModule shaderModule;
    };
}