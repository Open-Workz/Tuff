#include "GLFW.h"

#include "GLFW/glfw3.h"

#include "../../Tuff.Core/Common/Common.h"
#include "../../Tuff.Core/Platform/WindowSettings.h"

namespace Tuff::Backend::GLFW {
    namespace {
        GLFWwindow* gWindow = nullptr;
        GLFWmonitor* gMonitor = nullptr;
        const GLFWvidmode* gVideoMode = nullptr;
        Core::Platform::WindowSettings gWindowSettings;
        int gCurrentWindowWidth = 0;
        int gCurrentWindowHeight = 0;
    }
    
    bool Init(API api, int width, int height, const std::string& title) {
        if (!glfwInit()) {
            return false;
        }
        gWindowSettings.Width = width;
        gWindowSettings.Height = height;
        gWindowSettings.Title = title;
        
        if (api == API::OPENGL) {
#ifdef __APPLE__
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#else
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
#endif
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);   
        }
        
        gMonitor = glfwGetPrimaryMonitor();
        gVideoMode = glfwGetVideoMode(gMonitor);
        
        if (gWindowSettings.WindowMode == WindowMode::WINDOWED) {
            gCurrentWindowWidth = gWindowSettings.Width;
            gCurrentWindowHeight = gWindowSettings.Height;
            gWindow = glfwCreateWindow(gWindowSettings.Width, gWindowSettings.Height, gWindowSettings.Title.c_str(), nullptr, nullptr);
        }
        else if (gWindowSettings.WindowMode == WindowMode::FULLSCREEN) {
            gCurrentWindowWidth = gVideoMode->width;
            gCurrentWindowHeight = gVideoMode->height;
            gWindow = glfwCreateWindow(gCurrentWindowWidth, gCurrentWindowHeight, gWindowSettings.Title.c_str(), gMonitor, nullptr);
        }
        
        if (!gWindow) {
            glfwTerminate();
            return false;
        }
        
        if (gWindowSettings.WindowMode == WindowMode::WINDOWED && gWindowSettings.WindowAlignment == WindowAlignment::CENTER) {
            glfwSetWindowPos(gWindow, (gVideoMode->width - gCurrentWindowWidth) / 2, (gVideoMode->height - gCurrentWindowHeight) / 2);
        }
        else if (gWindowSettings.WindowMode == WindowMode::WINDOWED && gWindowSettings.WindowAlignment == WindowAlignment::CENTER_HORIZONTAL) {
            glfwSetWindowPos(gWindow, (gVideoMode->width - gCurrentWindowWidth) / 2, gCurrentWindowHeight);
        }
        else if (gWindowSettings.WindowMode == WindowMode::WINDOWED && gWindowSettings.WindowAlignment == WindowAlignment::CENTER_VERTICAL) {
            glfwSetWindowPos(gWindow, gCurrentWindowWidth, (gVideoMode->height - gCurrentWindowHeight) / 2);
        }
        
        glfwMakeContextCurrent(gWindow);
        glfwSwapInterval(gWindowSettings.VSync ? 1 : 0);
        
        return true;
    }

    void BeginFrame() {
        glfwPollEvents();
    }

    void EndFrame() {
        glfwSwapBuffers(gWindow);
    }

    void Shutdown() {
        if (gWindow) {
            glfwDestroyWindow(gWindow);
            gWindow = nullptr;
        }
        glfwTerminate();
    }

    bool WindowIsOpen() {
        return gWindow && !glfwWindowShouldClose(gWindow);
    }

    void* GetWindowPtr() {
        return gWindow;
    }

    glm::ivec2 GetFramebufferSize() {
        int width = 0, height = 0;
        if (!gWindow) {
            return {width, height};
        }
        glfwGetFramebufferSize(gWindow, &width, &height);
        return {width, height};
    }

    glm::dvec2 GetCursorPos() {
        double x = 0, y = 0;
        if (!gWindow) {
            return {x, y};
        }
        glfwGetCursorPos(gWindow, &x, &y);
        return {x, y};
    }
}
