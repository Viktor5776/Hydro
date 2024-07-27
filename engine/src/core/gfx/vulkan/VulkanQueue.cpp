#include "VulkanQueue.h"

namespace Hydro::gfx
{
    VulkanQueue::VulkanQueue( VulkanDevice device, uint32_t queueIndex )
    {
        vkGetDeviceQueue( device.GetDevice(), device.GetQueueFamilyIndex(), queueIndex, &queue );
    }

    VkQueue VulkanQueue::GetQueue() const
    {
        return queue;
    }
}