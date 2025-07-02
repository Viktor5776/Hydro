#include "ViewportPanel.h"

#include <imgui.h>

namespace hydro::editor
{
    ViewportPanel::ViewportPanel(std::shared_ptr<gfx::Framebuffer> pFramebuffer)
        :
        pFramebuffer_(pFramebuffer)
    {}

    void ViewportPanel::Render()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

        ImGui::Begin(GetName().c_str());
        ImVec2 viewportSize = ImGui::GetContentRegionAvail();

        if ((viewportSize_.x != viewportSize.x || viewportSize_.y != viewportSize.y) &&
            viewportSize.x > 0 && viewportSize.y > 0) {

            viewportSize_ = { viewportSize.x, viewportSize.y };
            pFramebuffer_->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
        }
        
        ImGui::Image((ImTextureID)pFramebuffer_->GetColorAttachment(0)->GetNativeHandle(), ImVec2(viewportSize.x, viewportSize.y), ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();
        ImGui::PopStyleVar(2);
    }

    std::string ViewportPanel::GetName() const
    {
        return "Viewport";
    }

}
