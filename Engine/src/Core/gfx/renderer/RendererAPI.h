#pragma once
#include <memory>

namespace hydro::gfx
{
	class RendererAPI
	{
	public:
		enum class APIType
		{
			None,
			OpenGL
		};
	public:
		static APIType GetAPI() { return sAPI; }
	private:
		static APIType sAPI; 
	};
}