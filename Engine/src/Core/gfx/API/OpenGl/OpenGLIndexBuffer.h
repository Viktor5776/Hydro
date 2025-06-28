#pragma once
#include "../../Bindable/Buffer/IndexBuffer.h"

namespace hydro::gfx
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(const unsigned int* indices, size_t count);
		~OpenGLIndexBuffer();
		size_t GetCount() const override;
		void Bind() override;
	private:
		unsigned int EBO_ = 0;

		size_t count_;
	};
}