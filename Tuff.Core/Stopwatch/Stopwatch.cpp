#include "Stopwatch.h"

#include <chrono>

namespace Tuff::Core::Stopwatch {
    namespace {
        using Clock = std::chrono::steady_clock;
        Clock::time_point gStartTime;
        double gElapsedMs = 0.0;
        bool gRunning = false;
    }

    void Start() {
        gStartTime = Clock::now();
        gRunning = true;
    }

    void Stop() {
        if (!gRunning) return;
        auto endTime = Clock::now();
        gElapsedMs = std::chrono::duration<double, std::milli>(endTime - gStartTime).count();
        gRunning = false;
    }

    double GetElapsedTime() {
        return gElapsedMs;
    }
}