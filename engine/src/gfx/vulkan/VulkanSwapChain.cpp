#include "VulkanSwapChain.h"
#include "VulkanDevice.h"
#include "VulkanSurface.h"
#include <stdexcept>
#include <SDL2/SDL_vulkan.h>
#include <limits>
#include <algorithm>

#include <iostream>

namespace Hydro::gfx
{
    VulkanSwapChain::VulkanSwapChain( std::shared_ptr<VulkanDevice> device, VulkanPhysicalDevice& physicalDevice, VulkanSurface& surface, SDL_Window* window )
        :
        device( device )
    {
        SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport( physicalDevice.GetPhysicalDevice(), surface.GetSurface() );

        VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat( swapChainSupport.formats );
        VkPresentModeKHR presentMode = ChooseSwapPresentMode( swapChainSupport.presentModes );
        VkExtent2D extent = ChooseSwapExtent( swapChainSupport.capabilities, window );

        swapChainImageFormat = surfaceFormat.format;
        swapChainExtent = extent;

        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

        if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
            imageCount = swapChainSupport.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = surface.GetSurface();
        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        QueueFamilyIndices indices = FindQueueFamilies(physicalDevice.GetPhysicalDevice(), surface.GetSurface());
        uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

        if (indices.graphicsFamily != indices.presentFamily) {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        } else {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            createInfo.queueFamilyIndexCount = 0; // Optional
            createInfo.pQueueFamilyIndices = nullptr; // Optional
        }

        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;

        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;

        createInfo.oldSwapchain = VK_NULL_HANDLE;

        if (vkCreateSwapchainKHR(device->GetDevice(), &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
            throw std::runtime_error("failed to create swap chain!");
        }

        vkGetSwapchainImagesKHR(device->GetDevice(), swapChain, &imageCount, nullptr);
        swapChainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(device->GetDevice(), swapChain, &imageCount, swapChainImages.data());

        // Create image views
        swapChainImageViews.resize(swapChainImages.size());

        for( size_t i = 0; i < swapChainImages.size(); i++ )
        {
            VkImageViewCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            createInfo.image = swapChainImages[i];
            createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            createInfo.format = swapChainImageFormat;
            createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            createInfo.subresourceRange.baseMipLevel = 0;
            createInfo.subresourceRange.levelCount = 1;
            createInfo.subresourceRange.baseArrayLayer = 0;
            createInfo.subresourceRange.layerCount = 1;

            if( vkCreateImageView(device->GetDevice(), &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS )
            {
                throw std::runtime_error("failed to create image views!");
            }
        }
    }

    VulkanSwapChain::~VulkanSwapChain()
    {
        std::cout << "Destroying swap chain" << std::endl;
        
        for (auto imageView : swapChainImageViews) {
            vkDestroyImageView(device->GetDevice(), imageView, nullptr);
        }

        vkDestroySwapchainKHR(device->GetDevice(), swapChain, nullptr);
    }

    VkSwapchainKHR VulkanSwapChain::GetSwapChain() const
    {
        return swapChain;
    }

    SwapChainSupportDetails QuerySwapChainSupport( VkPhysicalDevice device, VkSurfaceKHR surface )
    {
        SwapChainSupportDetails details;

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR( device, surface, &details.capabilities );

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR( device, surface, &formatCount, nullptr );

        if( formatCount != 0 )
        {
            details.formats.resize( formatCount );
            vkGetPhysicalDeviceSurfaceFormatsKHR( device, surface, &formatCount, details.formats.data() );
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR( device, surface, &presentModeCount, nullptr );

        if( presentModeCount != 0 )
        {
            details.presentModes.resize( presentModeCount );
            vkGetPhysicalDeviceSurfacePresentModesKHR( device, surface, &presentModeCount, details.presentModes.data() );
        }

        return details;
    }

    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
    {
        for( const auto& availableFormat : availableFormats )
        {
            if( availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR )
            {
                return availableFormat;
            }
        }

        return availableFormats[0];
    }

    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
    {
        for( const auto& availablePresentMode : availablePresentModes )
        {
            if( availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR )
            {
                return availablePresentMode;
            }
        }

        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, SDL_Window* window )
    {
        if( capabilities.currentExtent.width != UINT32_MAX )
        {
            return capabilities.currentExtent;
        }
        else
        {
            int width, height;
            SDL_Vulkan_GetDrawableSize( window, &width, &height );

            VkExtent2D actualExtent = { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };

            actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
            actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

            return actualExtent;
        }
    }

    VkExtent2D VulkanSwapChain::GetSwapChainExtent() const
    {
        return swapChainExtent;
    }

    VkFormat VulkanSwapChain::GetSwapChainImageFormat() const
    {
        return swapChainImageFormat;
    }

    std::vector<VkImageView>&  VulkanSwapChain::GetSwapChainImageViews()
    {
        return swapChainImageViews;
    }
}