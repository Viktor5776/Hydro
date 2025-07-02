#pragma once
#include "Panel.h"
#include <Core/ImGui/ImGuiManager.h>

#include <vector>
#include <memory>

namespace hydro::editor
{
	class PanelManager
	{
	public:
		void Init();
		void Render();
		void AddPanel(const std::shared_ptr<Panel>& panel);
	private:
		std::vector<std::shared_ptr<Panel>> panels_;
		std::shared_ptr<ImGuiManager> pImGuiManager_;
	};
}