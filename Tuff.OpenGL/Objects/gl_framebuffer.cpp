#include "gl_framebuffer.h"

#include "../../Tuff.Backend/GLFW/GLFW.h"
#include "../../Tuff.Core/Logger/Logger.h"
#include "../Backend/gl_backend.h"

namespace OpenGL {
    void Framebuffer::UnbindTexture() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    void Framebuffer::ActivateTexture(uint8_t id) {
        glActiveTexture(GL_TEXTURE0 + id);
    }
}

namespace OpenGL {
    Framebuffer::~Framebuffer() {
        Destroy();
    }

    bool Framebuffer::Create(int width, int height, bool useDepth) {
        if (width <= 0 || height <= 0) {
            return false;
        }

        Destroy();

        mWidth = width;
        mHeight = height;
        mUseDepth = useDepth;

        glGenFramebuffers(1, &mHandle);
        glBindFramebuffer(GL_FRAMEBUFFER, mHandle);

        glGenTextures(1, &mColorTexture);
        glBindTexture(GL_TEXTURE_2D, mColorTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mColorTexture, 0);

        if (mUseDepth) {
            glGenRenderbuffers(1, &mDepthRenderbuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, mDepthRenderbuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mDepthRenderbuffer);
        }

        bool complete = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;

        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        if (!complete) {
            Tuff::Core::Logger::Error("Framebuffer::Create: Framebuffer is incomplete");
            Destroy();
            return false;
        }

        return true;
    }

    void Framebuffer::Destroy() {
        if (mDepthRenderbuffer) {
            glDeleteRenderbuffers(1, &mDepthRenderbuffer);
            mDepthRenderbuffer = 0;
        }

        if (mColorTexture) {
            glDeleteTextures(1, &mColorTexture);
            mColorTexture = 0;
        }

        if (mHandle) {
            glDeleteFramebuffers(1, &mHandle);
            mHandle = 0;
        }

        mWidth = 0;
        mHeight = 0;
        mUseDepth = true;
    }

    bool Framebuffer::Resize(int width, int height) {
        if (width <= 0 || height <= 0) {
            return false;
        }

        if (width == mWidth && height == mHeight) {
            return true;
        }

        return Create(width, height, mUseDepth);
    }

    void Framebuffer::Clear() const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Framebuffer::ClearColor() const {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Framebuffer::ClearDepth() const {
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    void Framebuffer::Bind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, mHandle);
        glViewport(0, 0, mWidth, mHeight);
    }

    void Framebuffer::BindTexture() const {
        glBindTexture(GL_TEXTURE_2D, mColorTexture);
    }

    void Framebuffer::Unbind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glm::ivec2 size = Tuff::Backend::GLFW::GetFramebufferSize();
        glViewport(0, 0, size.x, size.y);
    }

    GLuint Framebuffer::GetHandle() const {
        return mHandle;
    }
    
    GLuint Framebuffer::GetColorTexture() const {
        return mColorTexture;
    }

    int Framebuffer::GetWidth() const {
        return mWidth;
    }
    
    int Framebuffer::GetHeight() const {
        return mHeight;
    }
}