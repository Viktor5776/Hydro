#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <memory>
#include "VulkanInstance.h"

namespace Hydro::gfx
{
    class VulkanDebuger
    {
    public:
        VulkanDebuger( std::shared_ptr<VulkanInstance> instance );
        ~VulkanDebuger();
        static bool CheckValidationLayerSupport();
        static const std::vector<const char*> GetValidationLayers();
        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData);
    private:
        std::shared_ptr<VulkanInstance> instance;
        VkDebugUtilsMessengerEXT debugMessenger;
    };
}