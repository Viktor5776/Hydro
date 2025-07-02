#pragma once
#include "ImGuiManager.h"

namespace hydro
{
	class OpenGLImGuiManager : public ImGuiManager
	{
	public:
		~OpenGLImGuiManager();
		void Init(void* window, void* context) override;
		void NewFrame() override;
		void RenderDrawData(void* data) override;
		void ProcessEvent(void* event) override;
	};
}