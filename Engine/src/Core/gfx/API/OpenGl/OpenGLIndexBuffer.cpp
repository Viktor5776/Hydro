#include "OpenGLIndexBuffer.h"

#include <glad\glad.h>


namespace hydro::gfx
{

	OpenGLIndexBuffer::OpenGLIndexBuffer(const unsigned int* indices, size_t count)
		:
		count_(count)
	{
		glGenBuffers(1, &EBO_);

		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		if (EBO_ != 0) {
			glDeleteBuffers(1, &EBO_);
		}
	}

	size_t OpenGLIndexBuffer::GetCount() const
	{
		return count_;
	}

	void OpenGLIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
	}

}