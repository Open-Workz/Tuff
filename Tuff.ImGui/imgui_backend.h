#pragma once

namespace Tuff::ImGuiBackend {
    bool Init(void* window);
    void BeginFrame();
    void EndFrame();
    void Shutdown();
}