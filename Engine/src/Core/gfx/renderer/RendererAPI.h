#pragma once
#include "../Bindable/Buffer/VertexLayout.h"
#include "../Bindable/Buffer/VertexBuffer.h"
#include "../Bindable/Buffer/IndexBuffer.h"
#include "../Shader/Shader.h"

#include <glm\glm.hpp>

#include <memory>

namespace hydro::gfx
{
	class RendererAPI
	{
	public:
		enum class APIType
		{
			None,
			OpenGL
		};
	public:
		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(
			std::shared_ptr<VertexBuffer> vertexBuffer,
			std::shared_ptr<IndexBuffer> indexBuffer,
			const VertexLayout& layout,
			std::shared_ptr<Shader> shader) = 0;

		virtual void DrawLines(
			std::shared_ptr<VertexBuffer> vertexBuffer,
			std::shared_ptr<IndexBuffer> indexBuffer,
			const VertexLayout& layout,
			std::shared_ptr<Shader> shader) = 0;

		virtual void SetLineWidth(float width) = 0;

		static APIType GetAPI() { return sAPI_; }
		static std::shared_ptr<RendererAPI> Create();
	private:
		static APIType sAPI_; 
	};
}