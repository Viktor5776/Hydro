#pragma once
#include <string>
#include <Core/runtime/Runtime.h>
#include <Core/scene/Scene.h>



//Temp
#include <Core/gfx/API/OpenGl/OpenGLVertexBuffer.h>
#include <Core/gfx/API/OpenGl/OpenGLIndexBuffer.h>
#include <Core/gfx/API/OpenGl/OpenGLShader.h>
#include <Core/gfx/API/OpenGl/OpenGLContext.h>
#include <Core/gfx/API/OpenGl/OpenGLFramebuffer.h>
#include <Core/gfx/Bindable/Buffer/VertexLayout.h>
#include <Core/gfx/renderer/RendererCommand.h>

namespace hydro::runtime
{
	class EditorRuntime : public IRuntime
	{
	public:
		EditorRuntime(const std::string& name);
		int Run() override;
		scene::Scene scene_;


		//Temporary
		std::shared_ptr<gfx::GraphicsContext> context;
		std::shared_ptr<gfx::VertexBuffer> vertexBuffer;
		gfx::VertexLayout vertexLayout;
		std::shared_ptr<gfx::IndexBuffer> indexBuffer;
		std::shared_ptr<gfx::Shader> shader;
		std::shared_ptr<gfx::Framebuffer> frameBuffer;

		void OPENGL(int width, int height);
	};
}