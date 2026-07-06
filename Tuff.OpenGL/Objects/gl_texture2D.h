#pragma once

#include <string>
#include <glm.hpp>
#include <GL/glew.h>

namespace OpenGL {
    struct Texture2D {
        Texture2D() = default;
        ~Texture2D();

        Texture2D(const Texture2D&) = delete;
        Texture2D& operator=(const Texture2D&) = delete;

        Texture2D(Texture2D&& other) noexcept;
        Texture2D& operator=(Texture2D&& other) noexcept;

        bool Load(const std::string& path, bool flipVertically = true);
        bool Create(int width, int height, GLenum internalFormat = GL_RGBA8);

        void Bind(unsigned int slot = 0) const;
        void Unbind(unsigned int slot = 0) const;
        void BindImage(unsigned int unit, GLenum access, int level = 0) const;

        void Destroy();

        bool IsValid() const;
        GLuint GetHandle() const;
        GLenum GetInternalFormat() const;

        int GetWidth() const;
        int GetHeight() const;
        float GetAspect() const;
        int GetChannels() const;

        glm::vec4 GetUVMinMax(float tileSize, int row, int col) const;

    private:
        GLuint mHandle = 0;
        int mWidth = 0;
        int mHeight = 0;
        int mChannels = 0;
        GLenum mInternalFormat = GL_RGBA8;
    };   
}