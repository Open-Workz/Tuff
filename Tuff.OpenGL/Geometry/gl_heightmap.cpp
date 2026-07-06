#include "gl_heightmap.h"

#include <algorithm>
#include <cmath>
#include <stb_image.h>

namespace OpenGL {
    bool HeightMap::Load(const std::string& path) {
        mData = stbi_load(path.c_str(), &mWidth, &mHeight, &mChannels, 0);
        stbi_set_flip_vertically_on_load(true);
        return mData != nullptr;
    }

    float HeightMap::SampleNearest(float u, float v) const {
        u = std::clamp(u, 0.f, 1.f);
        v = std::clamp(v, 0.f, 1.f);
        const int x = static_cast<int>(u * static_cast<float>(mWidth - 1));
        const int y = static_cast<int>(v * static_cast<float>(mHeight - 1));
        const int index = (y * mWidth + x) * mChannels;
        return static_cast<float>(mData[index]) / 255.f;
    }
    
    float HeightMap::SampleBilinear(float u, float v) const {
        // 1. Clamp UV coordinates to the safe [0.0, 1.0] range
        u = std::clamp(u, 0.f, 1.f);
        v = std::clamp(v, 0.f, 1.f);

        // 2. Map UV to continuous pixel coordinate space
        const float pixelX = u * static_cast<float>(mWidth - 1);
        const float pixelY = v * static_cast<float>(mHeight - 1);

        // 3. Find the integer coordinates of the 4 surrounding pixels
        const int x0 = static_cast<int>(std::floor(pixelX));
        const int y0 = static_cast<int>(std::floor(pixelY));
        // Guard boundaries using clamp to handle the far edges (u=1.0, v=1.0)
        const int x1 = std::clamp(x0 + 1, 0, mWidth - 1);
        const int y1 = std::clamp(y0 + 1, 0, mHeight - 1);

        // 4. Calculate fractional distances (weights) between pixel centers [0.0, 1.0]
        const float tx = pixelX - static_cast<float>(x0);
        const float ty = pixelY - static_cast<float>(y0);

        // 5. Helper lambda to quickly fetch and normalize a single texel
        auto getTexel = [this](int x, int y) -> float {
            const int index = (y * mWidth + x) * mChannels;
            return static_cast<float>(mData[index]) / 255.f;
        };

        // 6. Fetch heights for the 4 surrounding pixels
        const float h00 = getTexel(x0, y0); // Top-Left
        const float h10 = getTexel(x1, y0); // Top-Right
        const float h01 = getTexel(x0, y1); // Bottom-Left
        const float h11 = getTexel(x1, y1); // Bottom-Right

        // 7. Perform the 3 linear interpolations (lerp)
        // Interpolate horizontally along the top two pixels
        const float topInterpolation    = h00 + tx * (h10 - h00);
        // Interpolate horizontally along the bottom two pixels
        const float bottomInterpolation = h01 + tx * (h11 - h01);
        // Interpolate vertically between the top and bottom results
        return topInterpolation + ty * (bottomInterpolation - topInterpolation);
    }

    void HeightMap::Free() {
        if (mData) {
            stbi_image_free(mData);
            mData = nullptr;
        }
    }
}
