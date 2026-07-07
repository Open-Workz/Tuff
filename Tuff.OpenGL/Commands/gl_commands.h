#pragma once

#include <string>

#include <GL/glew.h>
#include <glm.hpp>

namespace OpenGL {
    struct Shader;
    struct Framebuffer;
}

namespace OpenGL::Commands {
    
    GLuint GetUniformLocation(const std::string& name);
    
    void BindShader(const std::string& shader);
    void BindTexture2D(const std::string& name, int slot);
    
    void BlitFrameBuffer(const Framebuffer* framebufferPtr);
    
    void SetUniformBool(const std::string& name, bool enabled);
    void SetUniformInt(const std::string& name, int value);
    void SetUniformFloat(const std::string& name, float value);
    void SetUniformVec2(const std::string& name, glm::vec2 value);
    void SetUniformVec3(const std::string& name, glm::vec3 value);
    void SetUniformVec4(const std::string& name, glm::vec4 value);
    void SetUniformMat4(const std::string& name, const glm::mat4& matrix);
}