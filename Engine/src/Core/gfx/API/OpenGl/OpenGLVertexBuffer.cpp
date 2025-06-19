#include "OpenGLVertexBuffer.h"
#include <glad\glad.h>

#include <iostream>
#include <SDL3\SDL.h>

namespace hydro::gfx
{

	void OpenGLVertexBuffer::Create(const void* data, size_t size, const std::vector<LayoutElement>& layout)
	{
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);


		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

		unsigned int totalStride = 0;
		for (const auto& e : layout) {
			totalStride += Stride(e);
		}

		unsigned int offset = 0;
		for (int i = 0; i < layout.size(); i++) {
			auto elem = layout[i];
			glVertexAttribPointer(i, Size(elem), Type(elem), Normalized(elem), totalStride, (const void*)(uintptr_t)offset);
			glEnableVertexAttribArray(i);
			offset += Stride(elem);
		}
		
	}

	void OpenGLVertexBuffer::Bind()
	{
		glBindVertexArray(VAO);
	}

	constexpr GLenum OpenGLVertexBuffer::Type(LayoutElement elem)
	{
		switch (elem.type) {
		case VertexBuffer::FLOAT:
			return GL_FLOAT;
			break;
		case VertexBuffer::VEC2:
			return GL_FLOAT;
			break;
		case VertexBuffer::VEC3:
			return GL_FLOAT;
			break;
		case VertexBuffer::VEC4:
			return GL_FLOAT;
			break;
		}
	}

	constexpr unsigned int OpenGLVertexBuffer::Normalized(LayoutElement elem)
	{
		switch (elem.type) {
		case VertexBuffer::FLOAT:
			return GL_FALSE;
			break;
		case VertexBuffer::VEC2:
			return GL_FALSE;
			break;
		case VertexBuffer::VEC3:
			return GL_FALSE;
			break;
		case VertexBuffer::VEC4:
			return GL_FALSE;
			break;
		}
	}

	constexpr unsigned int OpenGLVertexBuffer::Stride(LayoutElement elem)
	{
		switch (elem.type) {
		case VertexBuffer::FLOAT:
			return sizeof(float);
			break;
		case VertexBuffer::VEC2:
			return sizeof(glm::vec2);
			break;
		case VertexBuffer::VEC3:
			return sizeof(glm::vec3);
			break;
		case VertexBuffer::VEC4:
			return sizeof(glm::vec4);
			break;
		}
	}

}