#pragma once

namespace Tuff::Core::Time {
    void Init();
    void BeginFrame();
    void Reset();
    float DeltaTime();
    float TotalTime();
    float MinDeltaTime();
    float MaxDeltaTime();
    float MinFPS();
    float MaxFPS();
}
