#pragma once

#include <GL/glew.h>

namespace OpenGL {
    struct  VertexBuffer {
        VertexBuffer() = default;
        ~VertexBuffer();

        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator=(const VertexBuffer&) = delete;

        VertexBuffer(VertexBuffer&& other) noexcept;
        VertexBuffer& operator=(VertexBuffer&& other) noexcept;

        void Create(const void* data, size_t size, GLenum usage = GL_STATIC_DRAW);
        void Bind() const;
        void SetData(const void* data, size_t size);
        void Unbind() const;
        void Destroy();

        GLuint GetId() const;
        bool IsValid() const;
    
    private:
        GLuint mId = 0;
    };   
}