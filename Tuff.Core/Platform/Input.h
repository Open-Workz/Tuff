#pragma once

namespace Tuff::Core::Platform::Input {
    bool Init(void* window);
    void BeginFrame();
    bool GetKey(int key);
    bool GetKeyDown(int key);
    bool GetKeyUp(int key);
    bool GetMouseButton(int button);
    bool GetMouseButtonDown(int button);
    bool GetMouseButtonUp(int button);
    double GetMouseDeltaX();
    double GetMouseDeltaY();
    double ScrollDelta();
}
