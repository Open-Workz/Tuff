#include "gl_texture2D.h"

#include <stb_image.h>

#include "../../Tuff.Core/Logger/Logger.h"
#include "../Utils/gl_common.h"

namespace OpenGL {
    Texture2D::~Texture2D() {
        Destroy();
    }

    Texture2D::Texture2D(Texture2D&& other) noexcept {
        *this = std::move(other);
    }

    Texture2D& Texture2D::operator=(Texture2D&& other) noexcept {
        if (this != &other) {
            Destroy();

            mHandle = other.mHandle;
            mWidth = other.mWidth;
            mHeight = other.mHeight;
            mChannels = other.mChannels;
            mInternalFormat = other.mInternalFormat;

            other.mHandle = 0;
            other.mWidth = 0;
            other.mHeight = 0;
            other.mChannels = 0;
            other.mInternalFormat = GL_RGBA8;
        }

        return *this;
    }

    bool Texture2D::Load(const std::string& path, bool flipVertically) {
        Destroy();

        stbi_set_flip_vertically_on_load(flipVertically ? 1 : 0);

        unsigned char* data = stbi_load(path.c_str(), &mWidth, &mHeight, &mChannels, 0);
        if (!data) {
            Tuff::Core::Logger::Error("Texture2D::Load", "Failed to load texture: ", path, "\n", stbi_failure_reason());
            return false;
        }

        mInternalFormat = Common::InternalFormatFromChannels2D(mChannels);
        GLenum dataFormat = Common::DataFormatFromChannels2D(mChannels);

        glGenTextures(1, &mHandle);
        glBindTexture(GL_TEXTURE_2D, mHandle);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexStorage2D(GL_TEXTURE_2D, 1, mInternalFormat, mWidth, mHeight);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mWidth, mHeight, dataFormat, GL_UNSIGNED_BYTE, data);

        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);

        return true;
    }

    bool Texture2D::Create(int width, int height, GLenum internalFormat) {
        Destroy();

        if (width <= 0 || height <= 0) {
            Tuff::Core::Logger::Error("Texture2D::Create", "Invalid texture dimensions: ", width, "x", height);
            return false;
        }

        int channels = Common::ChannelsFromInternalFormat2D(internalFormat);
        if (channels == 0) {
            Tuff::Core::Logger::Error("Texture2D::Create", "Unsupported 2D texture format: ", internalFormat);
            return false;
        }

        mWidth = width;
        mHeight = height;
        mChannels = channels;
        mInternalFormat = internalFormat;

        glGenTextures(1, &mHandle);
        glBindTexture(GL_TEXTURE_2D, mHandle);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexStorage2D(GL_TEXTURE_2D, 1, internalFormat, width, height);

        glBindTexture(GL_TEXTURE_2D, 0);

        return true;
    }

    void Texture2D::Bind(unsigned int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, mHandle);
    }

    void Texture2D::Unbind(unsigned int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture2D::BindImage(unsigned int unit, GLenum access, int level) const {
        if (mHandle == 0) {
            return;
        }

        glBindImageTexture(unit, mHandle, level, GL_FALSE, 0, access, mInternalFormat);
    }

    void Texture2D::Destroy() {
        if (mHandle != 0) {
            glDeleteTextures(1, &mHandle);
            mHandle = 0;
        }

        mWidth = 0;
        mHeight = 0;
        mChannels = 0;
        mInternalFormat = GL_RGBA8;
    }

    bool Texture2D::IsValid() const {
        return mHandle != 0;
    }
        
    GLuint Texture2D::GetHandle() const {
        return mHandle;
    }
        
    GLenum Texture2D::GetInternalFormat() const {
        return mInternalFormat;
    }

    int Texture2D::GetWidth() const {
        return mWidth;
    }
        
    int Texture2D::GetHeight() const {
        return mHeight;
    }
        
    float Texture2D::GetAspect() const {
        return static_cast<float>(mWidth / mHeight);
    }
        
    int Texture2D::GetChannels() const {
        return mChannels;
    }

    glm::vec4 Texture2D::GetUVMinMax(float tileSize, int row, int col) const {
        float cols = static_cast<float>(mWidth) / tileSize;
        float rows = static_cast<float>(mHeight) / tileSize;

        float tileU = 1.0f / cols;
        float tileV = 1.0f / rows;

        glm::vec4 uv;
        uv.x = row * tileU;
        uv.y = col * tileV;
        uv.z = uv.x + tileU;
        uv.w = uv.y + tileV;

        return uv;
    }
}