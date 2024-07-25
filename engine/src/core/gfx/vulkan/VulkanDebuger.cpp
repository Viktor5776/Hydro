#include "VulkanDebuger.h"
#include <stdexcept>
#include "../../log/logger.h"

namespace Hydro::gfx
{
    VulkanDebuger::VulkanDebuger( std::shared_ptr<VulkanInstance> instance )
        :
        instance(instance)
    {
        #ifndef _DEBUG
            throw std::runtime_error("VulkanDebuger should only be used in debug builds");
        #endif

        VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = DebugCallback;
        createInfo.pUserData = nullptr;

        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance->GetInstance(), "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) 
        {
            if( func(instance->GetInstance(), &createInfo, nullptr, &debugMessenger) != VK_SUCCESS )
            {
                throw std::runtime_error("Failed to set up debug messenger");
            }
        } 
        else 
        {
            throw std::runtime_error("Failed to set up debug messenger");
        }
    }

    VulkanDebuger::~VulkanDebuger()
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance->GetInstance(), "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(instance->GetInstance(), debugMessenger, nullptr);
        }
    }

    bool VulkanDebuger::CheckValidationLayerSupport()
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char* layerName : GetValidationLayers()) {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        return true;
    }

    const std::vector<const char*> VulkanDebuger::GetValidationLayers()
    {
        return std::vector<const char*> {
            "VK_LAYER_KHRONOS_validation"
        };
    }

    VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebuger::DebugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData)
    {
        switch (messageSeverity)
        {
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
            LOG_DEBUG("Vulkan Validation Layer: " + std::string(pCallbackData->pMessage));
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
            LOG_INFO("Vulkan Validation Layer: " + std::string(pCallbackData->pMessage));
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            LOG_WARN("Vulkan Validation Layer: " + std::string(pCallbackData->pMessage));
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: 
            LOG_ERROR("Vulkan Validation Layer: " + std::string(pCallbackData->pMessage));
            break;
        default:
            LOG_TRACE("Vulkan Validation Layer: " + std::string(pCallbackData->pMessage));
            break;
        }

        return VK_FALSE;
    }
}