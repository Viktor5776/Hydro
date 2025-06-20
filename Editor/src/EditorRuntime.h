#pragma once
#include <string>
#include <Core/runtime/Runtime.h>
#include <Core/scene/Scene.h>



//Temp
#include <Core/gfx/API/OpenGl/OpenGLVertexBuffer.h>
#include <Core/gfx/API/OpenGl/OpenGLShader.h>

namespace hydro::runtime
{
	class EditorRuntime : public IRuntime
	{
	public:
		EditorRuntime(const std::string& name);
		int Run() override;
		scene::Scene scene_;


		//Temporary
		std::shared_ptr<gfx::IVertexBuffer> vertexBuffer;
		std::shared_ptr<gfx::IShader> shader;

		void OPENGL(int width, int height);
	};
}