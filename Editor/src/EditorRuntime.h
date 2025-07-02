#pragma once
#include <string>
#include <Core/runtime/Runtime.h>
#include <Core/scene/Scene.h>
#include "Panels\PanelManager.h"


//Temp
#include <Core/gfx/Bindable/Buffer/VertexBuffer.h>
#include <Core/gfx/Bindable/Buffer/IndexBuffer.h>
#include <Core/gfx/Shader/Shader.h>
#include <Core/gfx/renderer/GraphicsContext.h>
#include <Core/gfx/Bindable/Framebuffer.h>
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
		editor::PanelManager panelManager_; 

		//Temporary
		std::shared_ptr<gfx::GraphicsContext> context;
		std::shared_ptr<gfx::VertexBuffer> vertexBuffer;
		gfx::VertexLayout vertexLayout;
		std::shared_ptr<gfx::IndexBuffer> indexBuffer;
		std::shared_ptr<gfx::Shader> shader;
		std::shared_ptr<gfx::Framebuffer> frameBuffer;

		void DrawTest();
		void InitGFX();
	};
}