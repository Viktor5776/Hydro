#include "Framebuffer.h"
#include "../renderer/RendererAPI.h"
#include "../../utl/Assert.h"

#include "../API/OpenGl/OpenGLFramebuffer.h"

namespace hydro::gfx
{

    std::shared_ptr<Framebuffer> Framebuffer::Create(unsigned int width, unsigned int height)
    {
        switch (RendererAPI::GetAPI()) {
        case RendererAPI::APIType::OpenGL: return std::make_shared<OpenGLFramebuffer>(width, height);
        }

        hass(false).msg(L"Invalid API Type");
        return nullptr;
    }

}