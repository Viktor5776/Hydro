#include "VertexLayout.h"
#include "../../../utl/Assert.h"

namespace hydro::gfx
{

	void VertexLayout::AddAttribute(const std::string& name, ShaderDataType type, bool normalized)
	{
		hass(type != ShaderDataType::None).msg(L"Cannot add attribute with type none");

		unsigned int offset = stride_;
		unsigned int location = static_cast<unsigned int>(attributes_.size());
		stride_ += ShaderDataTypeSize(type);

		attributes_.push_back(VertexAttribute{
			.name = name,
			.type = type,
			.location = location,
			.offset = offset,
			.normalized = normalized
		});
	}

	const std::vector<VertexAttribute>& VertexLayout::GetAttributes() const
	{
		return attributes_;
	}

	unsigned int VertexLayout::GetStride() const
	{
		return stride_;
	}

}
