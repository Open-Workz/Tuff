#pragma once

#include <GL/glew.h>
#include <glm.hpp>
#include <string>

namespace OpenGL {
    struct Shader {
        bool Load(const std::string& vertexPath, const std::string& fragmentPath);
        GLuint GetProgram() const;
    
    private:
        static bool ReadFile(const std::string& path, std::string& outSource);
        static GLuint Compile(GLenum type, const std::string& source, const std::string& path);

    private:
        GLuint mProgram = 0;
    };   
}
