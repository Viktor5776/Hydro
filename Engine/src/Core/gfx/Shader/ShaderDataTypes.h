#pragma once

namespace hydro::gfx
{
	enum class ShaderDataType {
		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

	unsigned int ShaderDataTypeSize(ShaderDataType type);
	unsigned int ShaderDataTypeComponentCount(ShaderDataType type);
}