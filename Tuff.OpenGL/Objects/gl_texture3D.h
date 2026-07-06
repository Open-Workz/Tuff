#pragma once

#include <GL/glew.h>

namespace OpenGL {
    struct Texture3D {
        Texture3D() = default;
        ~Texture3D();

        Texture3D(const Texture3D&) = delete;
        Texture3D& operator=(const Texture3D&) = delete;

        Texture3D(Texture3D&& other) noexcept;
        Texture3D& operator=(Texture3D&& other) noexcept;

        bool Create(int width, int height, int depth, GLenum internalFormat = GL_RGBA8);

        void Bind(unsigned int slot = 0) const;
        void Unbind(unsigned int slot = 0) const;
        void BindImage(unsigned int unit, GLenum access, int level = 0) const;

        void Destroy();

        bool IsValid() const;
        GLuint GetHandle() const;
        GLenum GetInternalFormat() const;

        int GetWidth() const;
        int GetHeight() const;
        int GetDepth() const;
        int GetChannels() const;

    private:
        GLuint mHandle = 0;
        int mWidth = 0;
        int mHeight = 0;
        int mDepth = 0;
        int mChannels = 0;
        GLenum mInternalFormat = GL_RGBA8;
    };   
}