#include "Transform.h"

#include <gtc/matrix_transform.hpp>

namespace Tuff::Core::Math {
    glm::mat4 Transform::GetMatrix() const {
        glm::mat4 model(1.0f);
        model = glm::translate(model, Position);
        model = glm::rotate(model, Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, Scale);
        return model;
    }
}
