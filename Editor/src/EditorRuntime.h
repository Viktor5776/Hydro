#pragma once
#include <string>
#include <Core/runtime/Runtime.h>
#include <Core/scene/Scene.h>

namespace hydro::runtime
{
	class EditorRuntime : public IRuntime
	{
	public:
		EditorRuntime(const std::string& name);
		int Run() override;
		scene::Scene scene_;
	};
}