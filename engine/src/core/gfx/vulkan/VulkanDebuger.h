#pragma once
#include <vulkan/vulkan.h>
#include <vector>

namespace Hydro::gfx
{
    class VulkanDebuger
    {
    public:
        VulkanDebuger( VkInstance instance );
        ~VulkanDebuger();
        static bool CheckValidationLayerSupport();
        static const std::vector<const char*> GetValidationLayers();
        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData);
    private:
        VkInstance instance; //TODO: MAKE SURE TO CHANGE THIS WHEN THE INSTANCE IS MOVED TO ITS OWN CLASS AND MAKE IT A SHARED POINTER
        VkDebugUtilsMessengerEXT debugMessenger;
    };
}