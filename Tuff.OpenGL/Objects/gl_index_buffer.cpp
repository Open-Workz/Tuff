#include "gl_index_buffer.h"

namespace OpenGL {
    IndexBuffer::~IndexBuffer() {
        Destroy();
    }

    IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept {
        mId = other.mId;
        mCount = other.mCount;

        other.mId = 0;
        other.mCount = 0;
    }

    IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept {
        if (this != &other) {
            Destroy();

            mId = other.mId;
            mCount = other.mCount;

            other.mId = 0;
            other.mCount = 0;
        }
        return *this;
    }

    void IndexBuffer::Create(const void* data, size_t size, GLsizei count, GLenum usage) {
        Destroy();

        mCount = count;

        glGenBuffers(1, &mId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
    }

    void IndexBuffer::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
    }

    void IndexBuffer::SetData(const void* data, size_t size, GLsizei count) {
        Bind();
        mCount = count;
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
    }

    void IndexBuffer::Unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::Destroy() {
        if (mId != 0) {
            glDeleteBuffers(1, &mId);
            mId = 0;
        }

        mCount = 0;
    }

    GLuint IndexBuffer::GetId() const {
        return mId;
    }

    GLsizei IndexBuffer::GetCount() const {
        return mCount;
    }

    bool IndexBuffer::IsValid() const {
        return mId != 0 && mCount > 0;
    }   
}
