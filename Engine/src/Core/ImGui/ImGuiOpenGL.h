#pragma once
#include "ImGuiManager.h"

namespace hydro
{
	class ImGuiOpenGL : public ImGuiManager
	{
	public:
		void Init(void* window, void* context) override;
	};
}