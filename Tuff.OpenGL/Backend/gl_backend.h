#pragma once

#include <vec4.hpp>

namespace Tuff::OpenGL::Backend {
    bool Init(void* window);
    void BeginFrame();
    
    void SetClearColor(glm::vec4 clearColor);
}