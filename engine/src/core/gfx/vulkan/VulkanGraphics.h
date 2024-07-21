#pragma once
#include "../IGraphics.h"

namespace Hydro::gfx
{
    class VulkanGraphics : public IGraphics
    {
    public:
        VulkanGraphics();
        ~VulkanGraphics() override;

        void Render() override;
    };
}