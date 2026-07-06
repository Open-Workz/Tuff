#include "gl_texture3D.h"

#include "../../Tuff.Core/Logger/Logger.h"
#include "../Utils/gl_common.h"

namespace OpenGL {
    Texture3D::~Texture3D() {
        Destroy();
    }

    Texture3D::Texture3D(Texture3D&& other) noexcept {
        *this = std::move(other);
    }

    Texture3D& Texture3D::operator=(Texture3D&& other) noexcept {
        if (this != &other) {
            Destroy();

            mHandle = other.mHandle;
            mWidth = other.mWidth;
            mHeight = other.mHeight;
            mDepth = other.mDepth;
            mChannels = other.mChannels;
            mInternalFormat = other.mInternalFormat;

            other.mHandle = 0;
            other.mWidth = 0;
            other.mHeight = 0;
            other.mDepth = 0;
            other.mChannels = 0;
            other.mInternalFormat = GL_RGBA8;
        }

        return *this;
    }

    bool Texture3D::Create(int width, int height, int depth, GLenum internalFormat) {
        Destroy();

        if (width <= 0 || height <= 0 || depth <= 0) {
            Tuff::Core::Logger::Error("Texture3D::Create", "Invalid texture dimensions: ", width, "x", height);
            return false;
        }

        int channels = Common::ChannelsFromInternalFormat3D(internalFormat);
        if (channels == 0) {
            Tuff::Core::Logger::Error("Texture3D::Create", "Unsupported 2D texture format: ", internalFormat);
            return false;
        }

        mWidth = width;
        mHeight = height;
        mDepth = depth;
        mChannels = channels;
        mInternalFormat = internalFormat;

        glGenTextures(1, &mHandle);
        glBindTexture(GL_TEXTURE_3D, mHandle);

        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        //glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexStorage3D(GL_TEXTURE_3D, 1, internalFormat, width, height, depth);

        glBindTexture(GL_TEXTURE_3D, 0);

        return true;
    }

    void Texture3D::Bind(unsigned int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_3D, mHandle);
    }

    void Texture3D::Unbind(unsigned int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_3D, 0);
    }

    void Texture3D::BindImage(unsigned int unit, GLenum access, int level) const {
        if (mHandle == 0)
            return;

        glBindImageTexture(unit, mHandle, level, GL_TRUE, 0, access, mInternalFormat);
    }

    void Texture3D::Destroy() {
        if (mHandle != 0)
        {
            glDeleteTextures(1, &mHandle);
            mHandle = 0;
        }

        mWidth = 0;
        mHeight = 0;
        mDepth = 0;
        mChannels = 0;
        mInternalFormat = GL_RGBA8;
    }

    bool Texture3D::IsValid() const {
        return mHandle != 0;
    }
    
    GLuint Texture3D::GetHandle() const {
        return mHandle;
    }
    
    GLenum Texture3D::GetInternalFormat() const {
        return mInternalFormat;
    }

    int Texture3D::GetWidth() const {
        return mWidth;
    }
    
    int Texture3D::GetHeight() const {
        return mHeight;
    }
    
    int Texture3D::GetDepth() const {
        return mDepth;
    }
    
    int Texture3D::GetChannels() const {
        return mChannels;
    }
}
