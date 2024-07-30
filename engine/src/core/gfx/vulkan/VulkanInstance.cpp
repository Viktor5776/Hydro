#include "VulkanInstance.h"
#include "VulkanDebuger.h"
#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

namespace Hydro::gfx
{
    VulkanInstance::VulkanInstance( SDL_Window* pWindow )
    {
        #ifdef _DEBUG
            if( !VulkanDebuger::CheckValidationLayerSupport() )
            {
                throw std::runtime_error("Validation layers requested, but not available!");
            }
        #endif

        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Testbed";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Hydro";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t sdlExtensionCount = 0;
        if(!SDL_Vulkan_GetInstanceExtensions(pWindow, &sdlExtensionCount, nullptr))
        {
            throw std::runtime_error("Failed to get required instance extensions");
        }
        std::vector<const char*> sdlExtensions(sdlExtensionCount);
        
        if (!SDL_Vulkan_GetInstanceExtensions(pWindow, &sdlExtensionCount, sdlExtensions.data())) 
        {
            throw std::runtime_error("Failed to get required instance extensions");
        }

        #ifdef _DEBUG
            sdlExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        #endif

        createInfo.enabledExtensionCount = static_cast<uint32_t>(sdlExtensions.size());
        createInfo.ppEnabledExtensionNames = sdlExtensions.data();

        #ifdef _DEBUG
            auto validationLayers = VulkanDebuger::GetValidationLayers();
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        #else
            createInfo.enabledLayerCount = 0;
        #endif

        if( vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS )
        {
            throw std::runtime_error("Failed to create instance");
        }
    }

    VulkanInstance::~VulkanInstance()
    {
        vkDestroyInstance(instance, nullptr);
    }

    VkInstance VulkanInstance::GetInstance() const
    {
        return instance;
    }
}