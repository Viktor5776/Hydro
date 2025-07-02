#pragma once
#include <memory>

namespace hydro
{
	class ImGuiManager
	{
	public:
		virtual ~ImGuiManager() = default;

		virtual void Init(void* window, void* context) = 0;
		virtual void NewFrame() = 0;
		virtual void RenderDrawData(void* data) = 0;
		virtual void ProcessEvent(void* event) = 0;

		static std::shared_ptr<ImGuiManager> Create();
	};
}