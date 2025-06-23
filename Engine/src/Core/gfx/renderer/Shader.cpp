#include "Shader.h"
#include "RendererAPI.h"
#include "../../utl/Assert.h"

#include "../API/OpenGl/OpenGLShader.h"

namespace hydro::gfx
{

    std::shared_ptr<Shader> Shader::Create(std::filesystem::path vertSrc, std::filesystem::path pixelSrc)
    {
        switch (RendererAPI::GetAPI()) {
        case RendererAPI::APIType::OpenGL: return std::make_shared<OpenGLShader>(vertSrc, pixelSrc);
        }

        hass(false).msg(L"Invalid API Type");
        return nullptr;
    }

    std::shared_ptr<Shader> Shader::Create(std::string vertSrc, std::string pixelSrc)
    {
        switch (RendererAPI::GetAPI()) {
        case RendererAPI::APIType::OpenGL: return std::make_shared<OpenGLShader>(vertSrc, pixelSrc);
        }

        hass(false).msg(L"Invalid API Type");
        return nullptr;
    }

}
