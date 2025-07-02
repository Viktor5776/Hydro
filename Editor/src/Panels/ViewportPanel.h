#pragma once
#include "Panel.h"

#include <Core/gfx/Bindable/Framebuffer.h>

#include <glm\glm.hpp>

#include <memory>


namespace hydro::editor
{
	class ViewportPanel : public Panel
	{
	public:
		ViewportPanel(std::shared_ptr<gfx::Framebuffer> pFramebuffer);
		void Render() override;
		std::string GetName() const override;
	private:
		std::shared_ptr<gfx::Framebuffer> pFramebuffer_;
		glm::vec2 viewportSize_ = { 0.0f, 0.0f };
	};
}