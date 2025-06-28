#pragma once
#include "../../Shader/ShaderDataTypes.h"
#include <vector>
#include <string>

namespace hydro::gfx
{
	struct VertexAttribute {
		std::string name;
		ShaderDataType type = ShaderDataType::None;
		unsigned int location = 0;
		unsigned int offset = 0;
		bool normalized = false;
	};

	class VertexLayout {
	public:
		VertexLayout() = default;

		void AddAttribute(const std::string& name, ShaderDataType type, bool normalized = false);

		const std::vector<VertexAttribute>& GetAttributes() const;
		unsigned int GetStride() const;
	private:
		std::vector<VertexAttribute> attributes_;
		unsigned int stride_ = 0;
	};
}