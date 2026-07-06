#pragma once

#include <glm.hpp>

namespace Tuff::Core::Editor::Camera {
    void Init();
    void Update();
    void ImGui();
    
    void SetPosition(const glm::vec3& position);
    void SetForward(const glm::vec3& forward);
    void SetYaw(float yaw);
    void SetPitch(float pitch);
    void SetFov(float fov);
    void SetNearClip(float nearClip);
    void SetFarClip(float farClip);
    
    const glm::vec3& GetPosition();
    const glm::vec3& GetForward();
    const glm::vec3& GetRight();
    const glm::vec3& GetUp();
    
    float GetYaw();
    float GetPitch();
    
    float GetFov();
    float GetNearClip();
    float GetFarClip();
    
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
    bool IsMouseCaptured();
    
    // TODO: move these out of camera
    void ProcessMouseLook();
    void ProcessMovement();
}

