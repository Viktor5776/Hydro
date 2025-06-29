#include "OpenGLRendererAPI.h"

#include <glad\glad.h>

namespace hydro::gfx
{

	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_DEPTH_TEST);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
	}

	void OpenGLRendererAPI::SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer, const VertexLayout& layout, std::shared_ptr<Shader> shader)
	{
		//TODO: Store vao for multiple drawCalls
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		vertexBuffer->Bind();
		indexBuffer->Bind();

		// Set up attributes
		const auto& attrs = layout.GetAttributes();
		for (const auto& attr : attrs) {
			glEnableVertexAttribArray(attr.location);
			glVertexAttribPointer(
				attr.location,
				gfx::ShaderDataTypeComponentCount(attr.type),
				GL_FLOAT,
				attr.normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(uintptr_t)attr.offset
			);
		}

		shader->Bind();
		glDrawElements(GL_TRIANGLES, (GLsizei)indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

		glBindVertexArray(0);
		glDeleteVertexArrays(1, &vao);
	}

	void OpenGLRendererAPI::DrawLines(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer, const VertexLayout& layout, std::shared_ptr<Shader> shader)
	{
		//TODO: Store vao for multiple drawCalls
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		vertexBuffer->Bind();
		indexBuffer->Bind();

		// Set up attributes
		const auto& attrs = layout.GetAttributes();
		for (const auto& attr : attrs) {
			glEnableVertexAttribArray(attr.location);
			glVertexAttribPointer(
				attr.location,
				gfx::ShaderDataTypeComponentCount(attr.type),
				GL_FLOAT,
				attr.normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(uintptr_t)attr.offset
			);
		}

		shader->Bind();
		glDrawElements(GL_LINES, (GLsizei)indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

		glBindVertexArray(0);
		glDeleteVertexArrays(1, &vao);
	}

	void OpenGLRendererAPI::SetLineWidth(float width)
	{
		glLineWidth(width);
	}


}
