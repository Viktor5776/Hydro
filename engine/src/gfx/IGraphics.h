#pragma once
#include "Defines.h"
#include "../core/Window.h"

namespace Hydro::gfx
{
    class HAPI IGraphics
    {
    public:
        virtual ~IGraphics() = default;
        virtual void Render() = 0;
    };
} 