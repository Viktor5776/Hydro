#include "VulkanGraphics.h"
#include <iostream>
#include <memory>
#include <SDL2/SDL_vulkan.h>

namespace Hydro::gfx
{
    VulkanGraphics::VulkanGraphics( app::Window& window )
    {
        pWindow = window.GetWindow();
        instance = std::make_shared<VulkanInstance>(pWindow);

        #ifdef _DEBUG
            debugMessenger = std::make_unique<VulkanDebuger>(instance);
        #endif

        surface = std::make_unique<VulkanSurface>(instance, pWindow);
        physicalDevice = std::make_unique<VulkanPhysicalDevice>(instance->GetInstance(), surface->GetSurface());
        device = std::make_shared<VulkanDevice>(*physicalDevice);
        graphicsQueue = std::make_unique<VulkanQueue>(*device, 0, 0);
        presentQueue = std::make_unique<VulkanQueue>(*device, 0, 1);
        swapChain = std::make_unique<VulkanSwapChain>(device, *physicalDevice, *surface, pWindow);
        renderPass = std::make_unique<VulkanRenderPass>(device, swapChain->GetSwapChainImageFormat());
        graphicsPipeline = std::make_unique<VulkanGraphicsPipeline>(device, *swapChain, *renderPass);
        swapChainFramebuffers = std::make_unique<VulkanFramebuffer>(device, *swapChain, *renderPass);
        commandPool = std::make_unique<VulkanCommandPool>(device, *physicalDevice);
        vertexBuffer = std::make_unique<VulkanVertexBuffer>(device, *physicalDevice);
        commandBuffers = std::make_unique<VulkanCommandBuffer>(device, *commandPool, MAX_FRAMES_IN_FLIGHT);

        {
            //Create syncObjects
            imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
            renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
            inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

            VkSemaphoreCreateInfo semaphoreInfo = {};
            semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
            
            VkFenceCreateInfo fenceInfo = {};
            fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
            fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

            for( size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++ )
            {
                if (vkCreateSemaphore(device->GetDevice(), &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
                    vkCreateSemaphore(device->GetDevice(), &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS)
                {
                    throw std::runtime_error("Failed to create semaphores!");
                }


                if( vkCreateFence(device->GetDevice(), &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS )
                {
                    throw std::runtime_error("Failed to create fence!");
                }
            }

        }

    }

    VulkanGraphics::~VulkanGraphics()
    {
        vkDeviceWaitIdle(device->GetDevice());
        
        for( size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++ )
        {
            vkDestroySemaphore(device->GetDevice(), imageAvailableSemaphores[i], nullptr);
            vkDestroySemaphore(device->GetDevice(), renderFinishedSemaphores[i], nullptr);
            vkDestroyFence(device->GetDevice(), inFlightFences[i], nullptr);
        }
    }

    bool VulkanGraphics::RecreateSwapChain()
    {
        bool minimized = false;
        int windowFlags = SDL_GetWindowFlags(pWindow);
        minimized = (windowFlags & SDL_WINDOW_MINIMIZED) != 0;
        if( minimized )
        {
            return false;
        }

        vkDeviceWaitIdle(device->GetDevice());

        swapChain.reset();
        swapChain = std::make_unique<VulkanSwapChain>(device, *physicalDevice, *surface, pWindow);
        graphicsPipeline = std::make_unique<VulkanGraphicsPipeline>(device, *swapChain, *renderPass);
        swapChainFramebuffers = std::make_unique<VulkanFramebuffer>(device, *swapChain, *renderPass);
        return true;
    };

    void VulkanGraphics::Render()
    {
        vkWaitForFences(device->GetDevice(), 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

        uint32_t imageIndex = 0;
        VkResult result = vkAcquireNextImageKHR(device->GetDevice(), swapChain->GetSwapChain(), UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR) 
        {
            RecreateSwapChain();
            return;
        } 
        else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) 
        {
            throw std::runtime_error("failed to acquire swap chain image!");
        }

        vkResetFences(device->GetDevice(), 1, &inFlightFences[currentFrame]);

        vkResetCommandBuffer(commandBuffers->GetCommandBuffers()[currentFrame], 0);

        commandBuffers->RecordCommandBuffer(*renderPass, *swapChainFramebuffers, *swapChain, *graphicsPipeline, *vertexBuffer, imageIndex, currentFrame);

        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffers->GetCommandBuffers()[currentFrame];

        VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        if( vkQueueSubmit(graphicsQueue->GetQueue(), 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS )
        {
            throw std::runtime_error("Failed to submit draw command buffer!");
        }

        VkPresentInfoKHR presentInfo = {};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = {swapChain->GetSwapChain()};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;
        presentInfo.pImageIndices = &imageIndex;
        presentInfo.pResults = nullptr;

        result =  vkQueuePresentKHR(presentQueue->GetQueue(), &presentInfo);

        //NOTE: Maybe want to handle resize explicitly from SDL in the future
        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) 
        {
            if( !RecreateSwapChain() )
            {
                return;
            }
        } 
        else if (result != VK_SUCCESS) 
        {
            throw std::runtime_error("failed to present swap chain image!");
        }

        currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
    }
}