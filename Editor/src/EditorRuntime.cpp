#include "EditorRuntime.h"
#include <Core/log/Log.h>
#include <Core/ioc/Container.h>
#include <Core/win/SDLWindow.h>
#include <Core/input/SDLInput.h>
#include <Core/scene/Components.h>
#include <Core/scene/Entity.h>
#include <Core/ImGui/ImGuiOpenGL.h>

#include <Core/gfx/API/OpenGl/OpenGLContext.h>


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

    unsigned int renderedTexture;
    static void OPENGL(int width, int height)
    {
        // === Vertex Data ===
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        // === Vertex Buffer ===
        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO); // You must bind before vertex attrib setup
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // === Shaders ===
        const char* vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main() { gl_Position = vec4(aPos, 1.0); }\0";

        const char* fragmentShaderSource = "#version 330 core\n"
            "out vec4 color;\n"
            "void main() { color = vec4(1.0, 0.5, 0.2, 1.0); }\0";

        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);

        unsigned int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // === Framebuffer + Texture ===
        unsigned int frameBuffer;
        glGenFramebuffers(1, &frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

        glGenTextures(1, &renderedTexture);
        glBindTexture(GL_TEXTURE_2D, renderedTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderedTexture, 0);

        // === Depth Renderbuffer ===
        unsigned int depthBuffer;
        glGenRenderbuffers(1, &depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

        // Set draw buffers (optional for single target)
        GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
        glDrawBuffers(1, drawBuffers);

        hass(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE); // Your own assert macro

        // === Draw to the framebuffer ===
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glViewport(0, 0, width, height);
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        // === Done rendering to framebuffer ===
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    int EditorRuntime::Run()
    {
        auto pWin = ioc::Get().Resolve<win::IWindow>();
        auto pInput = std::dynamic_pointer_cast<input::SDLInput>(ioc::Get().Resolve<input::IInput>());

        pInput->LoadBindingsFromFile("BaseInputBindings.json");
       
        SDL_Window* pWindow = dynamic_cast<win::SDLWindow*>(pWin.get())->GetWindow();

        //OpenGL Boot Function 
        ioc::Get().Register<gfx::GraphicsContext>([&] {
            return std::make_shared<gfx::OpenGLContext>(pWindow);
        });

        auto pContext = ioc::Get().Resolve<gfx::GraphicsContext>();
        pContext->Init();
        
        //Needed for initilizeing ImGui with OpenGL
        auto glContext = std::dynamic_pointer_cast<gfx::OpenGLContext>(ioc::Get().Resolve<gfx::GraphicsContext>());


        //Init ImGui with openGL
        ioc::Get().Resolve<ImGuiManager>()->Init(pWindow,&glContext);
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
            ImGui::Image((ImTextureID)(intptr_t)renderedTexture, ImVec2(viewportSize.x, viewportSize.y), ImVec2(0, 1), ImVec2(1, 0));
            ImGui::End();
            ImGui::PopStyleVar(2);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            pContext->SwapBuffers();
            
        }

        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();

        return 0;
    }

}