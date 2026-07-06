#pragma once

#include <string>

namespace OpenGL {
    struct HeightMap {
        bool Load(const std::string& path);
        float SampleNearest(float u, float v) const;
        float SampleBilinear(float u, float v) const;
        void Free();
        
    private:
        int mWidth = 0;
        int mHeight = 0;
        int mChannels = 0;
        unsigned char* mData = nullptr;
    };
}
