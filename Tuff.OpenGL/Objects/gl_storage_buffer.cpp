#include "gl_storage_buffer.h"

namespace OpenGL {
    StorageBuffer::~StorageBuffer() {
        Destroy();
    }

    StorageBuffer::StorageBuffer(StorageBuffer&& other) noexcept {
        mId = other.mId;
        other.mId = 0;
    }

    StorageBuffer& StorageBuffer::operator=(StorageBuffer&& other) noexcept {
        if (this != &other) {
            Destroy();

            mId = other.mId;
            other.mId = 0;
        }

        return *this;
    }

    void StorageBuffer::Create() {
        if (mId == 0) {
            glGenBuffers(1, &mId);
        }
    }

    void StorageBuffer::Destroy() {
        if (mId != 0) {
            glDeleteBuffers(1, &mId);
            mId = 0;
        }
    }

    void StorageBuffer::SetData(const void* data, GLsizeiptr size, GLenum usage) {
        Create();

        glBindBuffer(GL_SHADER_STORAGE_BUFFER, mId);
        glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, usage);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }

    void StorageBuffer::BindBase(GLuint binding) const {
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, mId);
    }

    bool StorageBuffer::IsValid() const {
        return mId != 0;
    }

    GLuint StorageBuffer::GetId() const {
        return mId;
    }
}