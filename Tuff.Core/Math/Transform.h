#pragma once
#include <glm.hpp>

namespace Tuff::Core::Math {
    struct Transform {
        glm::vec3 Position{ 0.0f, 0.0f, 0.0f };
        glm::vec3 Rotation{ 0.0f, 0.0f, 0.0f };
        glm::vec3 Scale{ 1.0f, 1.0f, 1.0f };
        glm::mat4 GetMatrix() const;
    };
};
