#pragma once
#include "../Bindable.h"

#include <memory>

namespace hydro::gfx
{
	class IndexBuffer : public Bindable
	{
	public:
		virtual ~IndexBuffer() = default;
		virtual size_t GetCount() const = 0;
		static std::shared_ptr<IndexBuffer> Create(const unsigned int* indices, size_t count);
	};
}