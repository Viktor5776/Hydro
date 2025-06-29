#pragma once
#include "../../Shader/Shader.h"

namespace hydro::gfx
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(std::filesystem::path vertSrc, std::filesystem::path fragSrc);
		OpenGLShader(std::string vertSrc, std::string fragSrc);
		~OpenGLShader();
		void Bind() override;
	private:
		void CreateProgram(unsigned int vertexShader, unsigned int fragmentShader);
		std::string LoadShader(std::filesystem::path path);
		void CheckCompileErrors(unsigned int shader, const std::string& type);
	private:
		unsigned int shaderProgram_ = 0;
	};
}