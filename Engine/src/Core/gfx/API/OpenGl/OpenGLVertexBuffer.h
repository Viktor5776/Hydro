#pragma once
#include "../../renderer/VertexBuffer.h"

namespace hydro::gfx
{
	class OpenGLVertexBuffer : public IVertexBuffer
	{
	public:
		void Create(const void* data, size_t size, const std::vector<LayoutElement>&) override;
		void Bind() override;
	private:
		static constexpr unsigned int Type(LayoutElement elem);
		static constexpr unsigned int Normalized(LayoutElement elem);
		static constexpr unsigned int Stride(LayoutElement elem);
	private:
		unsigned int VBO = 0;
		unsigned int VAO = 0;
	};
}