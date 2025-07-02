#pragma once
#include  "../../renderer/GraphicsContext.h"

#include <SDL3\SDL.h>


namespace hydro::gfx
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(SDL_Window* pWindow);
		~OpenGLContext();

		void Init() override;
		void SwapBuffers() override;
		void* GetNativeHandle() override;
	private:
		SDL_GLContext context_;
		SDL_Window* pWindow_;
	};
}