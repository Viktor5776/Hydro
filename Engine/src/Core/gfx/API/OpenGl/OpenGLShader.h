#pragma once
#include "../../renderer/Shader.h"

namespace hydro::gfx
{
	class OpenGLShader : public IShader
	{
	public:
		void Create(std::filesystem::path vertSrc, std::filesystem::path fragSrc) override;
		void Create(std::string vertSrc, std::string fragSrc) override;
		void Bind() override;
	private:
		void CreateProgram(unsigned int vertexShader, unsigned int fragmentShader);
	private:
		unsigned int shaderProgram = 0;
	};
}