#include "Texture.h"
#include "../renderer/RendererAPI.h"
#include "../../utl/Assert.h"

#include "../API/OpenGl/OpenGLTexture.h"

namespace hydro::gfx
{

    std::shared_ptr<Texture> Texture::Create(unsigned int width, unsigned int height, Type type, Format format, unsigned int slot, const void* data)
    {
        switch (RendererAPI::GetAPI()) {
        case RendererAPI::APIType::OpenGL: return std::make_shared<OpenGLTexture>(width, height, type, format, slot, data);
        }

        hass(false).msg(L"Invalid API Type");
        return nullptr;
    }

}