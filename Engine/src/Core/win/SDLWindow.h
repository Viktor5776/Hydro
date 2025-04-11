#pragma once
#include "Window.h"
#include <memory>

struct SDL_Window;
struct SDL_Surface;

namespace hydro::win
{
	class SDLWindow : public IWindow
	{
	public:
		SDLWindow(std::pair<int,int> pos, std::pair<int, int> size, const std::string& name, size_t flags = 0);
		~SDLWindow();
		void SetName(const std::string& name) override;
		void SetPos(std::pair<int, int> pos) override;
		void SetSize(std::pair<int, int> size) override;
	private:
		std::string name_;
		std::pair<int, int> pos_;
		std::pair<int, int> size_;
		SDL_Window* pWindow_;
		SDL_Surface* pSurface_;
	};
}