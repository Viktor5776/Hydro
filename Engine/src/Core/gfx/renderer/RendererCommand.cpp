#include "RendererCommand.h"

namespace hydro::gfx
{
	std::shared_ptr<RendererAPI> RenderCommand::rendererAPI_ = RendererAPI::Create();

	void RenderCommand::Init()
	{
		rendererAPI_->Init();
	}

	void RenderCommand::SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
	{
		rendererAPI_->SetViewport(x, y, width, height);
	}

	void RenderCommand::SetClearColor(const glm::vec4& color)
	{
		rendererAPI_->SetClearColor(color);
	}

	void RenderCommand::Clear()
	{
		rendererAPI_->Clear();
	}

	void RenderCommand::DrawIndexed(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer, const VertexLayout& layout, std::shared_ptr<Shader> shader)
	{
		rendererAPI_->DrawIndexed(vertexBuffer, indexBuffer, layout, shader);
	}

	void RenderCommand::DrawLines(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer, const VertexLayout& layout, std::shared_ptr<Shader> shader)
	{
		rendererAPI_->DrawLines(vertexBuffer, indexBuffer, layout, shader);
	}

	void RenderCommand::SetLineWidth(float width)
	{
		rendererAPI_->SetLineWidth(width);
	}

}