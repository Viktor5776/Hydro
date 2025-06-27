#include "VertexBuffer.h"
#include "../../renderer/RendererAPI.h"
#include "../../../utl/Assert.h"

#include "../../API/OpenGl/OpenGLVertexBuffer.h"

namespace hydro::gfx
{

    std::shared_ptr<VertexBuffer> VertexBuffer::Create(const void* data, size_t size, const std::vector<LayoutElement>& layout)
    {
        switch (RendererAPI::GetAPI()) {
        case RendererAPI::APIType::OpenGL: return std::make_shared<OpenGLVertexBuffer>(data,size,layout);
        }

        hass(false).msg(L"Invalid API Type");
        return nullptr;
    }

}
