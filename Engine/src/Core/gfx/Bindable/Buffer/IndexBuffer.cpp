#include "IndexBuffer.h"
#include "../../renderer/RendererAPI.h"
#include "../../../utl/Assert.h"

#include "../../API/OpenGl/OpenGLIndexBuffer.h"

namespace hydro::gfx
{

    std::shared_ptr<IndexBuffer> IndexBuffer::Create(const unsigned int* indices, size_t count)
    {
        switch (RendererAPI::GetAPI()) {
        case RendererAPI::APIType::OpenGL: return std::make_shared<OpenGLIndexBuffer>(indices, count);
        }

        hass(false).msg(L"Invalid API Type");
        return nullptr;
    }

}
