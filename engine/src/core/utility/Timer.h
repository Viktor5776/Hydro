#pragma once
#include <chrono>
#include "defines.h"

namespace Hydro::utlity
{
    class HAPI Timer
    {
    public:
        Timer();
        float Peek() const;
        float Mark();
    private:
        std::chrono::steady_clock::time_point last;
    };
}