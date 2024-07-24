#include "VulkanGraphics.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <memory>

namespace Hydro::gfx
{
    VulkanGraphics::VulkanGraphics( app::Window& window )
    {
        pWindow = window.GetWindow();
        CreateInstance();
        #ifdef _DEBUG
            debugMessenger = std::make_unique<VulkanDebuger>(instance);
        #endif
    }

    VulkanGraphics::~VulkanGraphics()
    {
        //NOTE: everything created with the instance need to be destoryed before the instance is destroyed
        vkDestroyInstance(instance, nullptr);
    }

    void VulkanGraphics::Render()
    {
        
    }

    //Private
    void VulkanGraphics::CreateInstance()
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
            sdlExtensionCount += 1;
        #endif

        createInfo.enabledExtensionCount = sdlExtensionCount;
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
}