#pragma once
#include "defines.h"

namespace Hydro::gfx
{
    class HAPI IGraphics
    {
    public:
        virtual ~IGraphics() = default;
        virtual void Render() = 0;
    };
} 