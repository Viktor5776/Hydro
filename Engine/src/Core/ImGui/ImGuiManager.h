#pragma once

namespace hydro
{
	class ImGuiManager
	{
	public:
		virtual ~ImGuiManager() = default;

		virtual void Init(void* window, void* context) = 0;
	};
}