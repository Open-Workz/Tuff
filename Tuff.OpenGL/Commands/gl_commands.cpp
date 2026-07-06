#include "gl_commands.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "../../Tuff.Backend/GLFW/GLFW.h"
#include "../Resource/gl_resource_manager.h"
#include "../Objects/gl_shader.h"
#include "../Objects/gl_texture2D.h"
#include "../Objects/gl_framebuffer.h"

namespace OpenGL::Commands {
    namespace {
        Shader* gCurrentShader = nullptr;
        Texture2D* gCurrentTexure = nullptr;
    }

    GLuint GetUniformLocation(const std::string& name) {
        if (!gCurrentShader) {
            return -1;
        }
        return gCurrentShader->GetProgram();
    }

    void BindShader(const std::string& shader) {
        Shader* shader_ptr = ResourceManager::GetShaderPointer(shader);
        if (!shader_ptr) {
            return;
        }
        
        if (shader_ptr == gCurrentShader) {
            return;
        }
        
        gCurrentShader = shader_ptr;
        glUseProgram(gCurrentShader->GetProgram());
    }

    void BindTexture2D(const std::string& name, int slot) {
        Texture2D* texture_ptr = ResourceManager::GetTexture2DPointer(name);
        if (!texture_ptr) {
            return;
        }
        
        gCurrentTexure = texture_ptr;
        gCurrentTexure->Bind(slot);
    }

    void BlitFrameBuffer(const Framebuffer* framebufferPtr) {
        glm::ivec2 size = Tuff::Backend::GLFW::GetFramebufferSize();
        glBindFramebuffer(GL_READ_FRAMEBUFFER, framebufferPtr->GetHandle());
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // fix me later
        
        glBlitFramebuffer(
            0, 0, size.x, size.y,
            0, 0, size.x, size.y,
            GL_DEPTH_BUFFER_BIT,
            GL_NEAREST
        );

        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    }

    void SetUniformBool(const std::string& name, bool enabled) {
        if (const GLuint program = GetUniformLocation(name)) {
            const GLint location = glGetUniformLocation(program, name.c_str());
            if (location == -1) { return; }
            glUniform1i(location, enabled ? 1 : 0);
        }
    }
    
    void SetUniformInt(const std::string& name, int value) {
        if (const GLuint program = GetUniformLocation(name)) {
            const GLint location = glGetUniformLocation(program, name.c_str());
            if (location == -1) { return; }
            glUniform1i(location, value);   
        }
    }

    void SetUniformFloat(const std::string& name, float value) {
        if (const GLuint program = GetUniformLocation(name)) {
            const GLint location = glGetUniformLocation(program, name.c_str());
            if (location == -1) { return; }
            glUniform1f(location, value);   
        }
    }

    void SetUniformVec2(const std::string& name, glm::vec2 value) {
        if (const GLuint program = GetUniformLocation(name)) {
            const GLint location = glGetUniformLocation(program, name.c_str());
            if (location == -1) { return; }
            glUniform2f(location, value.x, value.y);   
        }
    }

    void SetUniformVec3(const std::string& name, glm::vec3 value) {
        if (const GLuint program = GetUniformLocation(name)) {
            const GLint location = glGetUniformLocation(program, name.c_str());
            if (location == -1) { return; }
            glUniform3f(location, value.x, value.y, value.z);   
        }
    }

    void SetUniformVec4(const std::string& name, glm::vec4 value) {
        if (const GLuint program = GetUniformLocation(name)) {
            const GLint location = glGetUniformLocation(program, name.c_str());
            if (location == -1) { return; }
            glUniform4f(location, value.x, value.y, value.z, value.w);   
        }
    }

    void SetUniformMat4(const std::string& name, const glm::mat4& matrix) {
        if (const GLuint program = GetUniformLocation(name)) {
            const GLint location = glGetUniformLocation(program, name.c_str());
            if (location == -1) { return; }
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
        }
    }
}
