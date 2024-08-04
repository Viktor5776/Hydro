#include "VulkanGraphicsPipeline.h"
#include "VulkanShaderModule.h"


#include <iostream>

namespace Hydro::gfx
{
    VulkanGraphicsPipeline::VulkanGraphicsPipeline( std::shared_ptr<VulkanDevice> device )
        : device( device )
    {
        //HACK: Hardcoded shader filenames
        VulkanShaderModule vertShader( device, "shaders/VertexTest.spv" );
        VulkanShaderModule fragShader( device, "shaders/FragmentTest.spv" );

        VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
        vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vertShaderStageInfo.module = vertShader.GetShaderModule();
        vertShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
        fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        fragShaderStageInfo.module = fragShader.GetShaderModule();
        fragShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

        std::cout << shaderStages << std::endl;
    }

    VulkanGraphicsPipeline::~VulkanGraphicsPipeline()
    {
    }
}