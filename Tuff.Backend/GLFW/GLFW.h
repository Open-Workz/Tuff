#pragma once

#include <string>

#include <vec2.hpp>

#include "../../Tuff.Core/Common/Common.h"

namespace Tuff::Backend::GLFW {
    bool Init(API api, int width, int height, const std::string& title);
    void BeginFrame();
    void EndFrame();
    void Shutdown();
    
    bool WindowIsOpen();
    
    void* GetWindowPtr();
    glm::ivec2 GetFramebufferSize();
    glm::dvec2 GetCursorPos();
}