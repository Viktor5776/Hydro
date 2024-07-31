#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <memory>

struct SDL_Window;

namespace Hydro::gfx
{
    class VulkanPhysicalDevice;
    class VulkanDevice;
    class VulkanSurface;

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    SwapChainSupportDetails QuerySwapChainSupport( VkPhysicalDevice device, VkSurfaceKHR surface );
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, SDL_Window* window);

    class VulkanSwapChain
    {
    public:
        VulkanSwapChain( std::shared_ptr<VulkanDevice> device, VulkanPhysicalDevice& physicalDevice, VulkanSurface& surface, SDL_Window* window );
        ~VulkanSwapChain();
        VkSwapchainKHR GetSwapChain() const;
    private:
        std::shared_ptr<VulkanDevice> device;
        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
    };
}