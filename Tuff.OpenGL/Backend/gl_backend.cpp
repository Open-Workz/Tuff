#include "gl_backend.h"

#include <GL/glew.h>
#include <glfw/glfw3.h>

#include <vec2.hpp>

namespace Tuff::OpenGL::Backend {
    namespace {
        GLFWwindow* gWindow = nullptr;
        glm::vec4 gClearColor = glm::vec4(0.05f, 0.05f, 0.05f, 1.0f);
        glm::ivec2 gFramebufferSize{0, 0};
    }
    
    bool Init(void* window) {
        if (glewInit() != GLEW_OK) {
            return false;
        }
        gWindow = static_cast<GLFWwindow*>(window);      
        glfwGetFramebufferSize(gWindow, &gFramebufferSize.x, &gFramebufferSize.y);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        return true;
    }
    
    void BeginFrame() {
        if (!gWindow) {return;}
        glfwGetFramebufferSize(gWindow, &gFramebufferSize.x, &gFramebufferSize.y);
        glViewport(0, 0, gFramebufferSize.x, gFramebufferSize.y);
        glClearColor(gClearColor.x, gClearColor.y, gClearColor.z, gClearColor.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void SetClearColor(glm::vec4 clearColor) {
        gClearColor = clearColor;
    }
}
