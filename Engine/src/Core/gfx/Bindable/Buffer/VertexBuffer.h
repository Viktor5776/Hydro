#pragma once
#include "../Bindable.h"

#include <memory>

namespace hydro::gfx
{
	class VertexBuffer : public Bindable
	{
	public:
		virtual ~VertexBuffer() = default;
		virtual void SetData(const void* data, size_t size) = 0;
		static std::shared_ptr<VertexBuffer> Create(const void* data, size_t size);
	};
}