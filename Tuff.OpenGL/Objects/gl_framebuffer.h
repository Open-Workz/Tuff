#pragma once

#include <cstdint>

#include <GL/glew.h>

namespace OpenGL {
    struct Framebuffer {
        Framebuffer() = default;
        ~Framebuffer();

        Framebuffer(const Framebuffer&) = delete;
        Framebuffer& operator=(const Framebuffer&) = delete;

        bool Create(int width, int height, bool useDepth = true);
        void Destroy();
        bool Resize(int width, int height);
        void Clear() const;
        void ClearColor() const;
        void ClearDepth() const;

        void Bind() const;
        void BindTexture() const;
        void Unbind() const;

        GLuint GetHandle() const;
        GLuint GetColorTexture() const;

        int GetWidth() const;
        int GetHeight() const;
        
        static void UnbindTexture();
        static void ActivateTexture(uint8_t id);

    private:
        GLuint mHandle = 0;
        GLuint mColorTexture = 0;
        GLuint mDepthRenderbuffer = 0;

        int mWidth = 0;
        int mHeight = 0;
        bool mUseDepth = true;
    };
}