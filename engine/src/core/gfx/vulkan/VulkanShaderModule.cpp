#include "VulkanShaderModule.h"
#include <fstream>

namespace Hydro::gfx
{
    VulkanShaderModule::VulkanShaderModule( std::shared_ptr<VulkanDevice> device, const std::string& filename )
        : device( device )
    {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);
        
        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);
        file.seekg(0);
        file.read(buffer.data(), fileSize);
        file.close(); 

        VkShaderModuleCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = buffer.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(buffer.data());

        if (vkCreateShaderModule(device->GetDevice(), &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create shader module!");
        }
    }

    VulkanShaderModule::~VulkanShaderModule()
    {
        vkDestroyShaderModule( device->GetDevice(), shaderModule, nullptr );
    }

    VkShaderModule VulkanShaderModule::GetShaderModule() const
    {
        return shaderModule;
    }
}