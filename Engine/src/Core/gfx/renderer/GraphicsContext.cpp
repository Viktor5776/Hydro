#include "GraphicsContext.h"
#include "../../utl/Assert.h"
#include "RendererAPI.h"

#include "../API/OpenGl/OpenGLContext.h"


namespace hydro::gfx
{

    std::shared_ptr<GraphicsContext> GraphicsContext::Create(SDL_Window* window)
    {
        switch (RendererAPI::GetAPI()) {
        case RendererAPI::APIType::OpenGL: return std::make_shared<OpenGLContext>(window);
        }

        hass(false).msg(L"Invalid API Type");
        return nullptr;
    }

}