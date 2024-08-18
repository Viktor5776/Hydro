#pragma once
#include "Defines.h"
#include "../app/Window.h"

namespace Hydro::gfx
{
    class HAPI IGraphics
    {
    public:
        virtual ~IGraphics() = default;
        virtual void Render() = 0;
    };
} 