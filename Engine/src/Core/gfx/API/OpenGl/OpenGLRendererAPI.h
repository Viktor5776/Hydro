#pragma once
#include "../../renderer/RendererAPI.h"

namespace hydro::gfx
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		
		void Init() override;
		void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) override;

		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;

		void DrawIndexed(
			std::shared_ptr<VertexBuffer> vertexBuffer, 
			std::shared_ptr<IndexBuffer>, 
			const VertexLayout& layout, 
			std::shared_ptr<Shader> shader) override;

		void DrawLines(
			std::shared_ptr<VertexBuffer> vertexBuffer,
			std::shared_ptr<IndexBuffer>, 
			const VertexLayout& layout, 
			std::shared_ptr<Shader> shader) override;

		void SetLineWidth(float width) override;

	};
}