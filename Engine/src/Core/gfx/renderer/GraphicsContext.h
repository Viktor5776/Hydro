#pragma once
#include <SDL3\SDL.h>

#include <memory>

namespace hydro::gfx
{
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		virtual void* GetNativeHandle() = 0;

		static std::shared_ptr<GraphicsContext> Create(SDL_Window* window);
	};
}