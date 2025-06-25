#include "Texture.h"
#include "RendererAPI.h"
#include "../../utl/Assert.h"

#include "../API/OpenGl/OpenGLTexture.h"

namespace hydro::gfx
{

    std::shared_ptr<Texture> Texture::Create(unsigned int width, unsigned int height, Type type, Format format, const void* data)
    {
        switch (RendererAPI::GetAPI()) {
        case RendererAPI::APIType::OpenGL: return std::make_shared<OpenGLTexture>(width, height, type, format, data);
        }

        hass(false).msg(L"Invalid API Type");
        return nullptr;
    }

}