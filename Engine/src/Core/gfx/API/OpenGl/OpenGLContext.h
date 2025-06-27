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

		virtual void Init() override;
		virtual void SwapBuffers() override;

		SDL_GLContext& GetContext();
	private:
		SDL_GLContext context_;
		SDL_Window* pWindow_;
	};
}