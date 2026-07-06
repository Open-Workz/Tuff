#pragma once

#include <GL/glew.h>

namespace OpenGL {
    struct IndexBuffer {
        IndexBuffer() = default;
        ~IndexBuffer();

        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer& operator=(const IndexBuffer&) = delete;

        IndexBuffer(IndexBuffer&& other) noexcept;
        IndexBuffer& operator=(IndexBuffer&& other) noexcept;

        void Create(const void* data, size_t size, GLsizei count, GLenum usage = GL_STATIC_DRAW);
        void Bind() const;
        void SetData(const void* data, size_t size, GLsizei count);
        void Unbind() const;
        void Destroy();

        GLuint GetId() const;
        GLsizei GetCount() const;
        bool IsValid() const;
    
    private:
        GLuint mId = 0;
        GLsizei mCount = 0;
    };   
}