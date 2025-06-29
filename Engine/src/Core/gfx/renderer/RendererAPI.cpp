#include "RendererAPI.h"
#include "../../utl/Assert.h"
#include "RendererAPI.h"

#include "../API/OpenGl/OpenGLRendererAPI.h"

namespace hydro::gfx
{
    //For now we only have OpenGL backend
    RendererAPI::APIType RendererAPI::sAPI_ = APIType::OpenGL;

    std::shared_ptr<RendererAPI> RendererAPI::Create()
    {
        switch (RendererAPI::GetAPI()) {
        case RendererAPI::APIType::OpenGL: return std::make_shared<OpenGLRendererAPI>();
        }

        hass(false).msg(L"Invalid API Type");
        return nullptr;
    }
}