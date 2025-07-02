#include "EditorRuntime.h"
#include <Core/log/Log.h>
#include <Core/ioc/Container.h>
#include <Core/ioc/Singletons.h>
#include <Core/win/SDLWindow.h>
#include <Core/input/SDLInput.h>
#include <Core/scene/Components.h>
#include <Core/scene/Entity.h>

#include "Panels\ViewportPanel.h"

#include <SDL3/SDL.h>

namespace hydro::runtime
{
    EditorRuntime::EditorRuntime(const std::string& name)
        :
        scene_("Scene")
    {

        //Init with SDL Window manager
        ioc::Get().Register<win::IWindow>([=] {
            return std::make_shared<win::SDLWindow>(std::pair{ 100,100 }, std::pair{ 1280,720 }, name, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        });

        ioc::Sing().Register<input::IInput>([] {
            return std::make_shared<input::SDLInput>();
        });

        ioc::Get().Register<ImGuiManager>([] {
            return ImGuiManager::Create();
        });

        
    }

    void EditorRuntime::DrawTest()
    {
        frameBuffer->Bind();
        gfx::RenderCommand::SetClearColor({ 0.2f,0.2f,0.3f,1.0f });
        gfx::RenderCommand::Clear();
        
        if (ioc::Sing().Resolve<input::IInput>()->IsActionHeld("A")) {
            gfx::RenderCommand::DrawLines(vertexBuffer, indexBuffer, vertexLayout, shader);
        }
        else {
            gfx::RenderCommand::DrawIndexed(vertexBuffer, indexBuffer, vertexLayout, shader);
        }
        frameBuffer->Unbind();
    }

    void EditorRuntime::InitGFX()
    {
        auto pWin = ioc::Get().Resolve<win::IWindow>();
        SDL_Window* pWindow = dynamic_cast<win::SDLWindow*>(pWin.get())->GetWindow();

        //Context
        context = gfx::GraphicsContext::Create(pWindow);
        context->Init();

        //Vertex Data
        float vertices[] = {
            -.5f, -.5f, 0.0f,1.0f,0.0f,0.0f,
             .5f, -.5f, 0.0f,0.0f,1.0f,0.0f,
             .5f,  .5f, 0.0f,0.0f,0.0f,1.0f,
             -.5f, .5f, 0.0f,1.0f,0.0f,1.0f
        };

        vertexLayout.AddAttribute("pos", gfx::ShaderDataType::Float3);
        vertexLayout.AddAttribute("color", gfx::ShaderDataType::Float3);

        //Vetex Buffer
        vertexBuffer = gfx::VertexBuffer::Create(
            vertices,
            sizeof(vertices)
        );

        //Index buffer
        std::vector<unsigned int> indices = {
            0,1,2,
            0,3,2
        };

        indexBuffer = gfx::IndexBuffer::Create(indices.data(), indices.size());

        //Shaders
        shader = gfx::Shader::Create(std::filesystem::path{ "Shaders/vertexShader.glsl" }, "Shaders/fragmentShader.glsl");

        frameBuffer = gfx::Framebuffer::Create(1, 1);
        frameBuffer->AddColorAttachment(gfx::Framebuffer::AttachmentType::Texture, gfx::Texture::Format::RGBA8);
        frameBuffer->SetDepthAttachment(gfx::Framebuffer::AttachmentType::Renderbuffer, gfx::Texture::Format::None);
    }

    int EditorRuntime::Run()
    {
        scene_.Deserialize("TestScene.json");


        auto pWin = ioc::Get().Resolve<win::IWindow>();
        auto pInput = std::dynamic_pointer_cast<input::SDLInput>(ioc::Sing().Resolve<input::IInput>());
        auto pImGuiManager = ioc::Get().Resolve<ImGuiManager>();

        pInput->LoadBindingsFromFile("BaseInputBindings.json");
        
        InitGFX();


        SDL_Window* pWindow = dynamic_cast<win::SDLWindow*>(pWin.get())->GetWindow();
        SDL_GLContext oContext = (SDL_GLContext)context->GetNativeHandle();
        //Init ImGui with openGL
        pImGuiManager->Init(pWindow,oContext);
        
        //Add Panels
        panelManager_.Init();
        panelManager_.AddPanel(std::make_shared<editor::ViewportPanel>(frameBuffer));

        bool quiting = false;
        while (!quiting) {

            pInput->Update();

            SDL_Event event;
            
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    quiting = true;
                }

                pImGuiManager->ProcessEvent(&event);
                pInput->UpdateEvent(event);
            }

            DrawTest();
            panelManager_.Render();

            context->SwapBuffers();
        }

        return 0;
    }

}