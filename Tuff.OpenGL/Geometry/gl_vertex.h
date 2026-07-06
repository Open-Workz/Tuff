#pragma once

#include <glm.hpp>

namespace OpenGL::Geometry {
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };   
}