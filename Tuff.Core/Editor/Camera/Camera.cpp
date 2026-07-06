#include "Camera.h"

#include <algorithm>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <gtc/matrix_transform.hpp>

#include "../../Tuff.Backend/Backend.h"
#include "../../Tuff.Backend/GLFW/GLFW.h"
#include "../../Tuff.Core/Platform/Input.h"
#include "../../Tuff.Core/Platform/Keys.h"
#include "../../Tuff.Core/Time/Time.h"
#include "../../Tuff.ImGui/imgui.h"

namespace Tuff::Core::Editor::Camera {
    namespace {
        glm::vec3 gPosition{0.f, 0.f, 600.f};
        glm::vec3 gForward{ 0.0, 0.0, 0.0};
        glm::vec3 gRight{ 1.0, 0.0, 0.0 };
        glm::vec3 gUp{ 0.0, 1.0, 0.0};
        glm::vec3 gVelocity{ 0.0, 0.0, 0.0 };
        glm::vec3 gWorldUp(0.0f, 1.0f, 0.0f);
    
        float gYaw = 180.f;
        float gPitch = 0.f;
        float gMaxPitch = 89.f;
        
        float gFov = 45.0f;
        float gNearClip = 0.1f;
        float gFarClip = 10000.0f;
        
        bool gMouseCaptured = false;
        
        // TODO: REMOVE ME LATER
        float gMoveSpeed = 50.f;
        float gAcceleration = 5.f;
        float gFriction = 5.f;
        float gMouseSensitivity = 0.0005f;
    }
    
    void Init() {
        void* window = Backend::GetWindowPtr();
        GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(window);
        glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        gYaw = glm::radians(gYaw);
        Update();
    }

    void Update() {
        ProcessMouseLook();
        float cosPitch = std::cos(gPitch);
        glm::vec3 forward{std::sin(gYaw) * cosPitch, std::sin(gPitch), std::cos(gYaw) * cosPitch};
        gForward = glm::normalize(forward);
        gRight = glm::normalize(glm::cross(gForward, gWorldUp));
        gUp = glm::normalize(glm::cross(gRight, gForward));
        ProcessMovement();
    }

    void ImGui() {
    }

    void SetPosition(const glm::vec3& position) {
        gPosition = position;
    }

    void SetForward(const glm::vec3& forward) {
        gForward = forward;
    }

    void SetYaw(float yaw) {
        gYaw = yaw;
    }

    void SetPitch(float pitch) {
        gPitch = pitch;
    }

    void SetFov(float fov) {
        gFov = fov;
    }

    void SetNearClip(float nearClip) {
        gNearClip = nearClip;
    }

    void SetFarClip(float farClip) {
        gFarClip = farClip;
    }

    const glm::vec3& GetPosition() {
        return gPosition;
    }

    const glm::vec3& GetForward() {
        return gForward;
    }

    const glm::vec3& GetRight() {
        return gRight;
    }

    const glm::vec3& GetUp() {
        return gUp;
    }

    float GetYaw() {
        return gYaw;
    }

    float GetPitch() {
        return gPitch;
    }

    float GetFov() {
        return gFov;
    }

    float GetNearClip() {
        return gNearClip;
    }

    float GetFarClip() {
        return gFarClip;
    }

    glm::mat4 GetViewMatrix() {
        return glm::lookAt(
            glm::vec3(gPosition),
            glm::vec3(gPosition + gForward),
            glm::vec3(gUp)
        );
    }

    glm::mat4 GetProjectionMatrix() {
        glm::ivec2 size = Backend::GLFW::GetFramebufferSize();
        if (size.y <= 0) { size.y = 1; }
        return glm::perspective(
            glm::radians(gFov),
            static_cast<float>(size.x) / static_cast<float>(size.y),
            gNearClip,
            gFarClip
        );
    }

    bool IsMouseCaptured() {
        return gMouseCaptured;
    }
    
    // TODO: MOVE ME
    void ProcessMouseLook() {
        GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(Backend::GLFW::GetWindowPtr());
        ImGuiIO& io = ImGui::GetIO();

        if (Platform::Input::GetKeyDown(Platform::Keys::GraveAccent) && !io.WantTextInput)
        {
            gMouseCaptured = !gMouseCaptured;
            glfwSetInputMode(glfwWindow, GLFW_CURSOR, gMouseCaptured ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
        }

        if (!gMouseCaptured || io.WantCaptureMouse)
        {
            return;
        }

        float deltaX = static_cast<float>(Platform::Input::GetMouseDeltaX());
        float deltaY = static_cast<float>(-Platform::Input::GetMouseDeltaY());
        gYaw -= deltaX * gMouseSensitivity;
        gPitch += deltaY * gMouseSensitivity;

        float pitchLimit = glm::radians(gMaxPitch);
        gPitch = std::clamp(gPitch, -pitchLimit, pitchLimit);
    }

    void ProcessMovement() {
        ImGuiIO& io = ImGui::GetIO();
        if (io.WantCaptureKeyboard) {
            return;
        }
        
        float deltaTime = Time::DeltaTime();
        glm::vec3 wishDir(0.0);

        glm::vec3 forward = glm::normalize(gForward);
        glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0, 1.0, 0.0)));
        glm::vec3 up(0.0, 1.0, 0.0);

        if (Platform::Input::GetKey(Platform::Keys::W))
            wishDir += forward;

        if (Platform::Input::GetKey(Platform::Keys::S))
            wishDir -= forward;

        if (Platform::Input::GetKey(Platform::Keys::A))
            wishDir -= right;

        if (Platform::Input::GetKey(Platform::Keys::D))
            wishDir += right;

        if (Platform::Input::GetKey(Platform::Keys::Q))
            wishDir += up;

        if (Platform::Input::GetKey(Platform::Keys::E))
            wishDir -= up;

        bool hasInput = glm::length(wishDir) > 0.0;

        if (hasInput)
            wishDir = glm::normalize(wishDir);

        float speed = gMoveSpeed;

        if (Platform::Input::GetKey(Platform::Keys::LeftShift))
            speed *= 2.f;
        
        if (Platform::Input::GetKey(Platform::Keys::LeftControl))
            speed *= 0.25f;

        glm::vec3 targetVelocity = wishDir * speed;

        float amount = hasInput ? gAcceleration : gFriction;
        float t = 1.f - std::exp(-amount * deltaTime);

        gVelocity = gVelocity + (targetVelocity - gVelocity) * t;
        gPosition += gVelocity * deltaTime;
    }
}
