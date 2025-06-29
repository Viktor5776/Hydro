#pragma once
#include "RendererAPI.h"

namespace hydro::gfx
{
	class RenderCommand
	{
	public:
		static void Init();
		static void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
		static void SetClearColor(const glm::vec4& color);
		static void Clear();

		static void DrawIndexed(
			std::shared_ptr<VertexBuffer> vertexBuffer,
			std::shared_ptr<IndexBuffer> indexBuffer,
			const VertexLayout& layout,
			std::shared_ptr<Shader> shader);

		static void DrawLines(
			std::shared_ptr<VertexBuffer> vertexBuffer,
			std::shared_ptr<IndexBuffer> indexBuffer,
			const VertexLayout& layout,
			std::shared_ptr<Shader> shader);

		static void SetLineWidth(float width);
	private:
		static std::shared_ptr<RendererAPI> rendererAPI_;
	};
}