#pragma once

#include <GL/glew.h>
#include <glm.hpp>
#include <string>

namespace OpenGL {
    struct Compute{
        bool Load(const std::string& path);
        void Bind() const;
        void Dispatch(int groupsX, int groupsY, int groupsZ) const;
        void Unbind() const;

        void SetInt(const std::string& name, int value);
        void SetFloat(const std::string& name, float value);
        void SetVec3(const std::string& name, glm::vec3 values);
        void SetVec4(const std::string& name, glm::vec4 values);
        void SetMat4(const std::string& name, const glm::mat4& matrix);
        void SetBool(const std::string& name, bool enabled);

        GLuint GetProgram() const;

    private:
        bool ReadFile(const std::string& path, std::string& outSource);
        GLuint Compile(GLenum type, const std::string& source, const std::string& path);

    private:
        GLuint mProgram = 0;
    };
}
