#include "SDLWindow.h"
#include "SDL3\SDL.h"
#include "../utl/Assert.h"
#include "../utl/String.h"
#include <format>

namespace hydro::win
{

	SDLWindow::SDLWindow(std::pair<int, int> pos, std::pair<int, int> size, const std::string& name, size_t flags)
		:
		pos_(pos),
		size_(size),
		name_(name)
	{
		//Depending on SDL usage may want to init system before this point
		hass(SDL_Init(SDL_INIT_VIDEO)).msg(std::format(L"Failed to init SDL3 library. SDL Error: {}", utl::ToWide(SDL_GetError()))).ex();

		pWindow_ = SDL_CreateWindow(name.c_str(), size.first, size.second, (SDL_WindowFlags)flags);

		hass(pWindow_).msg(std::format(L"Faild to create window. SDL Error: {}", utl::ToWide(SDL_GetError())));

		pSurface_ = SDL_GetWindowSurface(pWindow_);
		
		hass(pSurface_).msg(std::format(L"Failed to get the surface from the window. SDL Error: {}", utl::ToWide(SDL_GetError()))).ex();

		SetPos(pos);
	}

	SDLWindow::~SDLWindow()
	{
		SDL_DestroyWindow(pWindow_);

		SDL_QuitSubSystem(SDL_INIT_VIDEO);

		SDL_Quit();
	}

	void SDLWindow::SetName(const std::string& name)
	{
		hass(SDL_SetWindowTitle(pWindow_, name.c_str())).msg(std::format(L"Failed to set window name. SDL Error: {}", utl::ToWide(SDL_GetError())));
	}

	void SDLWindow::SetPos(std::pair<int, int> pos)
	{
		hass(SDL_SetWindowPosition(pWindow_, pos.first, pos.second)).msg(std::format(L"Failed to set window position. SDL Error: {}", utl::ToWide(SDL_GetError())));
	}

	void SDLWindow::SetSize(std::pair<int, int> size)
	{
		hass(SDL_SetWindowSize(pWindow_, size.first, size.second)).msg(std::format(L"Failed to set window size. SDL Error: {}", utl::ToWide(SDL_GetError())));
	}

	SDL_Window* SDLWindow::GetWindow()
	{
		return pWindow_;
	}

}