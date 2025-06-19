#pragma once
#include <filesystem>
#include <string>
#include <vector>

#include <glm\glm.hpp>

namespace hydro::gfx
{
	class IVertexBuffer
	{
	public:
		enum VertexTypes
		{
			FLOAT,
			VEC2,
			VEC3,
			VEC4,
		};
		struct LayoutElement
		{
			VertexTypes type;
			std::string name;
		};
		static constexpr unsigned int Size(VertexTypes type)
		{
			switch (type) {
			case IVertexBuffer::FLOAT:
				return 1;
				break;
			case IVertexBuffer::VEC2:
				return 2;
				break;
			case IVertexBuffer::VEC3:
				return 3;
				break;
			case IVertexBuffer::VEC4:
				return 4;
				break;
			}

		}
		static constexpr unsigned int Size(LayoutElement elem)
		{
			return Size(elem.type);
		}
	public:
		virtual ~IVertexBuffer() = default;
		virtual void Create(const void* data, size_t size, const std::vector<LayoutElement>&) = 0;
		virtual void Bind() = 0;
	};
}