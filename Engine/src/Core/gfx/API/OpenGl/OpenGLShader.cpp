#include "OpenGLShader.h"
#include "../../../utl/Assert.h"
#include "../../../utl/Exception.h"
#include "../../../utl/String.h"

#include <glad/glad.h>

#include <fstream>
#include <sstream>

namespace hydro::gfx
{

	OpenGLShader::OpenGLShader(std::filesystem::path vertSrc, std::filesystem::path fragSrc)
		:
		OpenGLShader(LoadShader(vertSrc), LoadShader(fragSrc))
	{}

	OpenGLShader::OpenGLShader(std::string vertSrc, std::string fragSrc)
	{
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const char* shaderSrc = vertSrc.c_str();
		glShaderSource(vertexShader, 1, &shaderSrc, nullptr);
		glCompileShader(vertexShader);
		CheckCompileErrors(vertexShader, "VERTEX");

		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		shaderSrc = fragSrc.c_str();
		glShaderSource(fragmentShader, 1, &shaderSrc, nullptr);
		glCompileShader(fragmentShader);
		CheckCompileErrors(fragmentShader, "FRAGMENT");

		CreateProgram(vertexShader, fragmentShader);
	}

	void OpenGLShader::CreateProgram(unsigned int vertexShader, unsigned int fragmentShader)
	{
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		CheckCompileErrors(shaderProgram, "PROGRAM");

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	std::string OpenGLShader::LoadShader(std::filesystem::path path)
	{
		std::ifstream file(path);
		hass(file).msg(L"Failed to open shader file: " + path.wstring());

		std::stringstream buffer;
		buffer << file.rdbuf();
		return buffer.str();
	}

	void OpenGLShader::CheckCompileErrors(unsigned int shader, const std::string& type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM") {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
				hass(false).msg(L"Error in shader compilation of type: " + utl::ToWide(type) + L"\n" + utl::ToWide({ infoLog }));
			}
		}
		else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
				hass(false).msg(L"Error in program linking\n" + utl::ToWide({ infoLog }));
			}
		}
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(shaderProgram);
	}


}