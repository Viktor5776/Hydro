#include "RendererAPI.h"
#include "../../utl/Assert.h"

namespace hydro::gfx
{
    //For now we only have OpenGL backend
    RendererAPI::APIType RendererAPI::sAPI = APIType::OpenGL;
}