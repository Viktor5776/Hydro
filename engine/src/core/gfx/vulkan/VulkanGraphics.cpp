#include "VulkanGraphics.h"
#include <iostream>
#include <memory>

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
        commandBuffer = std::make_unique<VulkanCommandBuffer>(device, *commandPool);

        {
            //Create syncObjects
            VkSemaphoreCreateInfo semaphoreInfo = {};
            semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

            if (vkCreateSemaphore(device->GetDevice(), &semaphoreInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS ||
                vkCreateSemaphore(device->GetDevice(), &semaphoreInfo, nullptr, &renderFinishedSemaphore) != VK_SUCCESS)
            {
                throw std::runtime_error("Failed to create semaphores!");
            }

            VkFenceCreateInfo fenceInfo = {};
            fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
            fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

            if( vkCreateFence(device->GetDevice(), &fenceInfo, nullptr, &inFlightFence) != VK_SUCCESS )
            {
                throw std::runtime_error("Failed to create fence!");
            }

        }

    }

    VulkanGraphics::~VulkanGraphics()
    {
        vkDeviceWaitIdle(device->GetDevice());
        
        vkDestroySemaphore(device->GetDevice(), imageAvailableSemaphore, nullptr);
        vkDestroySemaphore(device->GetDevice(), renderFinishedSemaphore, nullptr);
        vkDestroyFence(device->GetDevice(), inFlightFence, nullptr);

    }

    void VulkanGraphics::Render()
    {
        vkWaitForFences(device->GetDevice(), 1, &inFlightFence, VK_TRUE, UINT64_MAX);
        vkResetFences(device->GetDevice(), 1, &inFlightFence);

        uint32_t imageIndex;
        vkAcquireNextImageKHR(device->GetDevice(), swapChain->GetSwapChain(), UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

        vkResetCommandBuffer(commandBuffer->GetCommandBuffer(), 0);

        commandBuffer->RecordCommandBuffer(*renderPass, *swapChainFramebuffers, *swapChain, *graphicsPipeline, imageIndex);

        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = {imageAvailableSemaphore};
        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer->GetCommandBuffer();

        VkSemaphore signalSemaphores[] = {renderFinishedSemaphore};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        if( vkQueueSubmit(graphicsQueue->GetQueue(), 1, &submitInfo, inFlightFence) != VK_SUCCESS )
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

        vkQueuePresentKHR(presentQueue->GetQueue(), &presentInfo);

    }
}