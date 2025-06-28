#pragma once
#include "../../Bindable/Buffer/VertexBuffer.h"

namespace hydro::gfx
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(const void* data, size_t size);
		~OpenGLVertexBuffer();
		void SetData(const void* data, size_t size) override;
		void Bind() override;
	private:
		unsigned int VBO_ = 0;
	};
}