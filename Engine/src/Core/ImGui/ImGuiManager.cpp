#include "ImGuiManager.h"
#include "../gfx/renderer/RendererAPI.h"
#include "../utl/Assert.h"

#include "OpenGLImGuiManager.h"

namespace hydro
{

    std::shared_ptr<ImGuiManager> ImGuiManager::Create()
    {
        switch (gfx::RendererAPI::GetAPI()) {
        case gfx::RendererAPI::APIType::OpenGL: return std::make_shared<OpenGLImGuiManager>();
        }

        hass(false).msg(L"Invalid API Type");
        return nullptr;
    }

}