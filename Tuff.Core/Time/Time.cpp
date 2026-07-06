#include "Time.h"

#include <limits>
#include <algorithm>
#include <chrono>

namespace Tuff::Core::Time {
    
    namespace {
        using Clock = std::chrono::steady_clock;
        
        constexpr float MAX_DELTA_TIME = 0.1f;
        
        Clock::time_point gLastFrameTime;
        float gDeltaTime = 0.f;
        float gTotalTime = 0.f;
        float gMinDeltaTime = std::numeric_limits<float>::max();
        float gMaxDeltaTime = 0.0f;
    }
    
    void Init() {
        gLastFrameTime = Clock::now();
        gDeltaTime = 0.f;
        gTotalTime = 0.f;
    }
    
    void BeginFrame() {
        const Clock::time_point currentFrameTime = Clock::now();
        const float frameTime = std::chrono::duration<float>(currentFrameTime - gLastFrameTime).count();
        gDeltaTime = std::clamp(frameTime, 0.0f, MAX_DELTA_TIME);
        gTotalTime += gDeltaTime;
        gLastFrameTime = currentFrameTime;

        gMinDeltaTime = std::min(gDeltaTime, gMinDeltaTime);
        gMaxDeltaTime = std::max(gDeltaTime, gMaxDeltaTime);}

    void Reset() {
        gLastFrameTime = Clock::now();
        gDeltaTime = 0.f;
        gTotalTime = 0.f;
    }
    
    float DeltaTime() {
        return gDeltaTime;
    }

    float TotalTime() {
        return gTotalTime;
    }

    float MinDeltaTime() {
        return gMinDeltaTime;
    }

    float MaxDeltaTime() {
        return gMaxDeltaTime;
    }
    
    float MinFPS() {
        return gMaxDeltaTime > 0.0f ? 1.0f / gMaxDeltaTime : 0.0f;
    }

    float MaxFPS() {
        return gMinDeltaTime > 0.0f ? 1.0f / gMinDeltaTime : 0.0f;
    }
}
