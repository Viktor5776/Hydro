#include "PanelManager.h"

#include <Core/ioc/Singletons.h>

#include <imgui.h>

namespace hydro::editor
{
	void PanelManager::Init()
	{
		pImGuiManager_ = ioc::Sing().Resolve<ImGuiManager>();
	}

	void PanelManager::Render()
	{
		pImGuiManager_->NewFrame();

		// Docking space
		ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

		//Render Panels
		for (auto panel : panels_) {
			if (panel->isOpen) {
				panel->Render();
			}
		}

		ImGui::Render();
		pImGuiManager_->RenderDrawData(ImGui::GetDrawData());
	}

	void PanelManager::AddPanel(const std::shared_ptr<Panel>& panel)
	{
		panels_.push_back(panel);
	}

}