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

        ioc::Sing().Register<input::IInput>([] {
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
        
        //TEMP Use RenderCommands in future
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        vertexBuffer->Bind();
        indexBuffer->Bind();

        // Set up attributes
        const auto& attrs = vertexLayout.GetAttributes();
        for (const auto& attr : attrs) {
            glEnableVertexAttribArray(attr.location);
            glVertexAttribPointer(
                attr.location,
                gfx::ShaderDataTypeComponentCount(attr.type),
                GL_FLOAT,
                attr.normalized ? GL_TRUE : GL_FALSE,
                vertexLayout.GetStride(),
                (const void*)(uintptr_t)attr.offset
            );
        }
        
        shader->Bind();
        if (ioc::Sing().Resolve<input::IInput>()->IsActionHeld("Mouse4")) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

        glBindVertexArray(0);
        glDeleteVertexArrays(1, &vao);

        frameBuffer->Unbind();
    }

    int EditorRuntime::Run()
    {
        auto pWin = ioc::Get().Resolve<win::IWindow>();
        auto pInput = std::dynamic_pointer_cast<input::SDLInput>(ioc::Sing().Resolve<input::IInput>());

        pInput->LoadBindingsFromFile("BaseInputBindings.json");

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
            0,2,3
        };

        indexBuffer = gfx::IndexBuffer::Create(indices.data(), indices.size());

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
            OPENGL((int)viewportSize.x,(int)viewportSize.y);
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