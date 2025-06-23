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
		std::string LoadShader(std::filesystem::path path);
		void CheckCompileErrors(unsigned int shader, const std::string& type);
	private:
		unsigned int shaderProgram = 0;
	};
}