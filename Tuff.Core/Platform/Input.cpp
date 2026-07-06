#include "Input.h"

#include <GLFW/glfw3.h>

namespace Tuff::Core::Platform::Input {
    namespace {
        GLFWwindow* gWindow;
        bool gKeys[1024] = {};
        bool gKeysDown[1024] = {};
        bool gKeysUp[1024] = {};
        bool gMouseButtons[8] = {};
        bool gMouseButtonsDown[8] = {};
        bool gMouseButtonsUp[8] = {};
        double gMouseX = 0.0;
        double gMouseY = 0.0;
        double gLastMouseX = 0.0;
        double gLastMouseY = 0.0;
        double gMouseDeltaX = 0.0;
        double gMouseDeltaY = 0.0;
        double gScrollDelta = 0.0;
    }

    bool Init(void* window) {
        gWindow = static_cast<GLFWwindow*>(window);
        return gWindow != nullptr;
    }

    void BeginFrame() {
        gMouseDeltaX = 0.0;
        gMouseDeltaY = 0.0;
        for (int i = 0; i < 1024; i++) {
            bool current = glfwGetKey(gWindow, i) == GLFW_PRESS;
            gKeysDown[i] = current && !gKeys[i];
            gKeysUp[i] = !current && gKeys[i];
            gKeys[i] = current;
        }
        for (int i = 0; i < 8; i++)
        {
            bool current = glfwGetMouseButton(gWindow, i) == GLFW_PRESS;

            gMouseButtonsDown[i] = current && !gMouseButtons[i];
            gMouseButtonsUp[i] = !current && gMouseButtons[i];

            gMouseButtons[i] = current;
        }
        glfwGetCursorPos(gWindow, &gMouseX, &gMouseY);
        gMouseDeltaX = gMouseX - gLastMouseX;
        gMouseDeltaY = gMouseY - gLastMouseY;
        gLastMouseX = gMouseX;
        gLastMouseY = gMouseY;
    }

    bool GetKey(int key) {
        return gKeys[key];
    }

    bool GetKeyDown(int key) {
        return gKeysDown[key];
    }

    bool GetKeyUp(int key) {
        return gKeysUp[key];
    }

    bool GetMouseButton(int button) {
        return gMouseButtons[button];
    }

    bool GetMouseButtonDown(int button) {
        return gMouseButtonsDown[button];
    }

    bool GetMouseButtonUp(int button) {
        return gMouseButtonsUp[button];
    }
    
    double GetMouseDeltaX() {
        return gMouseDeltaX;
    }
    
    double GetMouseDeltaY() {
        return gMouseDeltaY;
    }

    double ScrollDelta() {
        return gScrollDelta;
    }
}
