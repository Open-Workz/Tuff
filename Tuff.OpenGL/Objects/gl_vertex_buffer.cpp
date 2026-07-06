#include "gl_vertex_buffer.h"

namespace OpenGL {
 
    VertexBuffer::~VertexBuffer() {
        Destroy();
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept {
        mId = other.mId;
        other.mId = 0;
    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept {
        if (this != &other) {
            Destroy();
            mId = other.mId;
            other.mId = 0;
        }

        return *this;
    }

    void VertexBuffer::Create(const void* data, size_t size, GLenum usage) {
        Destroy();

        glGenBuffers(1, &mId);
        glBindBuffer(GL_ARRAY_BUFFER, mId);
        glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    }

    void VertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, mId);
    }

    void VertexBuffer::SetData(const void* data, size_t size) {
        Bind();
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    void VertexBuffer::Unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::Destroy() {
        if (mId != 0)
        {
            glDeleteBuffers(1, &mId);
            mId = 0;
        }
    }

    GLuint VertexBuffer::GetId() const {
        return mId;
    }

    bool VertexBuffer::IsValid() const {
        return mId != 0;
    }     
}