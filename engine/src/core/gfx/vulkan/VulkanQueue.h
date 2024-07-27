#pragma once
#include <vulkan/vulkan.h>
#include "VulkanDevice.h"

namespace Hydro::gfx
{
    class VulkanQueue
    {
    public:
        VulkanQueue( VulkanDevice device, uint32_t queueIndex );
        VkQueue GetQueue() const;
    private:
        VkQueue queue;
    };
}