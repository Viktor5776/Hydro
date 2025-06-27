#pragma once
#include <filesystem>
#include <string>

namespace hydro::gfx
{
	class Shader
	{
	public:
		virtual ~Shader() = default;
		static std::shared_ptr<Shader> Create(std::filesystem::path vertSrc, std::filesystem::path pixelSrc);
		static std::shared_ptr<Shader> Create(std::string vertSrc, std::string pixelSrc);
		virtual void Bind() = 0;
	};
}