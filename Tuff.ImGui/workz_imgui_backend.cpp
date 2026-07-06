#include "workz_imgui_backend.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Tuff::ImGui::Backend {
    namespace {
        bool gInitialized = false;
    }
    bool Init(void* window) {
        if (gInitialized || window == nullptr) {
            return false;
        }
        
        GLFWwindow* gWindow = static_cast<GLFWwindow*>(window);
        
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        ImGui::StyleColorsDark();

        if (!ImGui_ImplGlfw_InitForOpenGL(gWindow, true)) {
            ImGui::DestroyContext();
            return false;   
        }

        if (!ImGui_ImplOpenGL3_Init("#version 460 core")) {
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
            return false;
        }
        gInitialized = true;
        return true; 
    }

    void BeginFrame() {
        if (!gInitialized) {return;}
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void EndFrame() {
        if (!gInitialized) {return;}
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void Shutdown() {
        if (!gInitialized) return;

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        gInitialized = false;
    }
}
