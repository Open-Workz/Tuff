#include "Backend.h"
#include "GLFW/GLFW.h"

#include "../Tuff.OpenGL/Backend/gl_backend.h"
#include "../Tuff.ImGui/imgui_backend.h"
#include "../Tuff.Core/Logger/Logger.h"
#include "../Tuff.Core/Platform/Input.h"
#include "../Tuff.Core/Time/Time.h"

namespace Tuff::Backend {
    namespace {
        API gAPI = API::OPENGL;
        bool gInitialized = false;
    }
    
    bool Init(API api, int width, int height, const std::string& title) {
        gAPI = api;
        
        if (!GLFW::Init(api, width, height, title)) {
            Core::Logger::Error("Tuff::Backend::Init", "Failed to initialize GLFW");
            return false;
        }
        
        if (api == API::OPENGL) {
            if (!OpenGL::Backend::Init(GetWindowPtr())) {
                Core::Logger::Error("Tuff::Backend::Init", "Failed to initialize OpenGL");
                GLFW::Shutdown();
                return false;
            }   
        }
        
        if (!ImGuiBackend::Init(GetWindowPtr())) {
            Core::Logger::Error("Tuff::Backend::Init", "Failed to initialize ImGuiBackend");
            GLFW::Shutdown();
            return false;
        }
        
        if (!Core::Platform::Input::Init(GetWindowPtr())) {
            Core::Logger::Error("Tuff::Backend::Init", "Failed to initialize input");
            GLFW::Shutdown();
            return false;
        }
        
        Core::Time::Init();
        
        gInitialized = true;
        return true;
    }
    
    void BeginFrame() {
        if (!gInitialized) {return;}
        Core::Time::BeginFrame();
        GLFW::BeginFrame();
        Core::Platform::Input::BeginFrame();
        if (gAPI == API::OPENGL) {
            OpenGL::Backend::BeginFrame();
        }
        ImGuiBackend::BeginFrame();
    }
    
    void EndFrame() {
        if (!gInitialized) {return;}
        ImGuiBackend::EndFrame();
        GLFW::EndFrame();
    }

    void* GetWindowPtr() {
        return GLFW::GetWindowPtr();
    }

    void Shutdown() {
        if (!gInitialized) {return;}
        ImGuiBackend::Shutdown();
        GLFW::Shutdown();
    }
}
