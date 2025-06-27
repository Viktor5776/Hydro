#include "EditorRuntime.h"
#include <Core/log/Log.h>
#include <Core/ioc/Container.h>
#include <Core/ioc/Singletons.h>
#include <Core/win/SDLWindow.h>
#include <Core/input/SDLInput.h>
#include <Core/scene/Components.h>
#include <Core/scene/Entity.h>
#include <Core/ImGui/ImGuiOpenGL.h>

#include <SDL3/SDL.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>
#include <glad/glad.h>

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

        ioc::Get().Register<input::IInput>([] {
            return std::make_shared<input::SDLInput>();
        });

        ioc::Get().Register<ImGuiManager>([] {
            return std::make_shared<ImGuiOpenGL>();
        });

    }

    void EditorRuntime::OPENGL(int width, int height)
    {

        frameBuffer->Resize(width, height);

        // === Draw to the framebuffer ===
        frameBuffer->Bind();
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shader->Bind();
        vertexBuffer->Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // === Done rendering to framebuffer ===
        frameBuffer->Unbind();
    }

    int EditorRuntime::Run()
    {
        auto pWin = ioc::Get().Resolve<win::IWindow>();
        auto pInput = std::dynamic_pointer_cast<input::SDLInput>(ioc::Get().Resolve<input::IInput>());

        pInput->LoadBindingsFromFile("BaseInputBindings.json");

        SDL_Window* pWindow = dynamic_cast<win::SDLWindow*>(pWin.get())->GetWindow();

        //Context
        context = gfx::GraphicsContext::Create(pWindow);
        context->Init();

        //Vertex Data
        float vertices[] = {
            -1.0f, -1.0f, 0.0f,1.0f,0.0f,0.0f,
             1.0f, -1.0f, 0.0f,0.0f,1.0f,0.0f,
             0.0f,  1.0f, 0.0f,0.0f,0.0f,1.0f
        };

        //Vetex Buffer
        vertexBuffer = gfx::VertexBuffer::Create(
            vertices,
            sizeof(vertices),
            std::vector<gfx::VertexBuffer::LayoutElement>{ {gfx::VertexBuffer::VEC3, "pos"}, { gfx::VertexBuffer::VEC3, "color" } }
        );

        //Shaders
        shader = gfx::Shader::Create(std::filesystem::path{"Shaders/vertexShader.glsl"}, "Shaders/fragmentShader.glsl");

        frameBuffer = gfx::Framebuffer::Create(1,1);
        frameBuffer->AddColorAttachment(gfx::Framebuffer::AttachmentType::Texture, gfx::Texture::Format::RGBA8);
        frameBuffer->SetDepthAttachment(gfx::Framebuffer::AttachmentType::Renderbuffer, gfx::Texture::Format::None);

        //Init ImGui with openGL
        ioc::Get().Resolve<ImGuiManager>()->Init(pWindow,&context);
        ImGuiIO& io = ImGui::GetIO();

        bool quiting = false;
        while (!quiting) {

            pInput->Update();

            SDL_Event event;

            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    quiting = true;
                }

                ImGui_ImplSDL3_ProcessEvent(&event);
                pInput->UpdateEvent(event);
            }

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL3_NewFrame();
            ImGui::NewFrame();

            // Docking space
            ImGui::DockSpaceOverViewport(0,ImGui::GetMainViewport());


            //Viewport
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            ImGui::Begin("Viewport");
            ImVec2 viewportSize = ImGui::GetContentRegionAvail();
            OPENGL(viewportSize.x,viewportSize.y);
            ImGui::Image((ImTextureID)frameBuffer->GetColorAttachment(0)->GetNativeHandle(), ImVec2(viewportSize.x, viewportSize.y), ImVec2(0, 1), ImVec2(1, 0));
            ImGui::End();
            ImGui::PopStyleVar(2);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            context->SwapBuffers();
            
        }

        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();

        return 0;
    }

}