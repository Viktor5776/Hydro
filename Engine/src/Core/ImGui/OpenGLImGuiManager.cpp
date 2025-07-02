#include "OpenGLImGuiManager.h"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>
#include <SDL3\SDL.h>
#include "../utl/Assert.h"


namespace hydro
{
    OpenGLImGuiManager::~OpenGLImGuiManager()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }

    void OpenGLImGuiManager::Init(void* pWindow, void* pContext)
	{
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGui::StyleColorsDark();

        // Make the GL context current before initializing ImGui OpenGL backend
        SDL_GL_MakeCurrent(static_cast<SDL_Window*>(pWindow), static_cast<SDL_GLContext>(pContext));

        // Initialize ImGui SDL3 backend for OpenGL
        ImGui_ImplSDL3_InitForOpenGL(static_cast<SDL_Window*>(pWindow), static_cast<SDL_GLContext>(pContext));
        ImGui_ImplOpenGL3_Init("#version 330");
	}

    void OpenGLImGuiManager::NewFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
    }

    void OpenGLImGuiManager::RenderDrawData(void* data)
    {
        ImGui_ImplOpenGL3_RenderDrawData((ImDrawData*)data);
    }

    void OpenGLImGuiManager::ProcessEvent(void* event)
    {
        ImGui_ImplSDL3_ProcessEvent((SDL_Event*)event);
    }

}