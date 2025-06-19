#pragma once
#include <filesystem>
#include <string>

namespace hydro::gfx
{
	class IShader
	{
	public:
		virtual ~IShader() = default;
		virtual void Create(std::filesystem::path vertSrc, std::filesystem::path pixelSrc) = 0;
		virtual void Create(std::string vertSrc, std::string pixelSrc) = 0;
		virtual void Bind() = 0;
	};
}