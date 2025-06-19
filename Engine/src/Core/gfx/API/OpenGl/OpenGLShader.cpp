#include "OpenGLShader.h"
#include "../../../utl/Assert.h"

#include <glad/glad.h>

namespace hydro::gfx
{

	void OpenGLShader::Create(std::filesystem::path vertSrc, std::filesystem::path fragSrc)
	{
	}

	void OpenGLShader::Create(std::string vertSrc, std::string fragSrc)
	{
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const char* shaderSrc = vertSrc.c_str();
		glShaderSource(vertexShader, 1, &shaderSrc, nullptr);
		glCompileShader(vertexShader);

		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		shaderSrc = fragSrc.c_str();
		glShaderSource(fragmentShader, 1, &shaderSrc, nullptr);
		glCompileShader(fragmentShader);

		CreateProgram(vertexShader, fragmentShader);
	}

	void OpenGLShader::CreateProgram(unsigned int vertexShader, unsigned int fragmentShader)
	{
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(shaderProgram);
	}


}