#include "ImGuiOpenGL.h"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>
#include <SDL3\SDL.h>
#include "../utl/Assert.h"


namespace hydro
{
	void ImGuiOpenGL::Init(void* pWindow, void* pContext)
	{
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        // Setup ImGui style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        ImGui_ImplSDL3_InitForOpenGL(static_cast<SDL_Window*>(pWindow), static_cast<SDL_Window*>(pContext));
        ImGui_ImplOpenGL3_Init("#version 330");
	}

}