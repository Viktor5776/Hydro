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
            std::cout << "Debug Build Created" << std::endl;
        #else
            std::cout << "Release Build Created" << std::endl;
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

        auto sdlExtensions = std::unique_ptr<const char*[]>(new const char*[sdlExtensionCount]);
        if (!SDL_Vulkan_GetInstanceExtensions(pWindow, &sdlExtensionCount, sdlExtensions.get())) 
        {
            throw std::runtime_error("Failed to get required instance extensions");
        }

        createInfo.enabledExtensionCount = sdlExtensionCount;
        createInfo.ppEnabledExtensionNames = sdlExtensions.get();
        createInfo.enabledLayerCount = 0;

        if( vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS )
        {
            throw std::runtime_error("Failed to create instance");
        }

    }
}