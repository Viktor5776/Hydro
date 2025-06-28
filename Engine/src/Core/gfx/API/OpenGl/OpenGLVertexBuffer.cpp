#include "OpenGLVertexBuffer.h"
#include <glad\glad.h>

namespace hydro::gfx
{

	OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, size_t size)
	{
		glGenBuffers(1, &VBO_);
		Bind();
		
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		if (VBO_ != 0) {
			glDeleteBuffers(1, &VBO_);
		}
	}

	void OpenGLVertexBuffer::SetData(const void* data, size_t size)
	{
		Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER,VBO_);
	}

}