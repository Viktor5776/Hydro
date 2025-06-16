#include "OpenGLContext.h"
#include "../../../utl/Assert.h"

#include <glad\glad.h>

namespace hydro::gfx
{
	OpenGLContext::OpenGLContext(SDL_Window* pWindow)
		:
		pWindow_(pWindow)
	{
		context_ = SDL_GL_CreateContext(pWindow_);
	}

	void OpenGLContext::Init()
	{
		SDL_GL_MakeCurrent(pWindow_, context_);

		hass(gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)).msg(L"Failed to initialize GLAD");
	}

	void OpenGLContext::SwapBuffers()
	{
		SDL_GL_SwapWindow(pWindow_);
	}

	SDL_GLContext& OpenGLContext::GetContext()
	{
		return context_;
	}

}