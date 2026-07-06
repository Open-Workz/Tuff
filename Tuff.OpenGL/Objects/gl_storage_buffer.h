#pragma once

#include <GL/glew.h>

namespace OpenGL {
    struct StorageBuffer {
        StorageBuffer() = default;
        ~StorageBuffer();

        StorageBuffer(const StorageBuffer&) = delete;
        StorageBuffer& operator=(const StorageBuffer&) = delete;

        StorageBuffer(StorageBuffer&& other) noexcept;
        StorageBuffer& operator=(StorageBuffer&& other) noexcept;

        void Create();
        void Destroy();

        void SetData(const void* data, GLsizeiptr size, GLenum usage = GL_DYNAMIC_DRAW);
        void BindBase(GLuint binding) const;

        bool IsValid() const;
        GLuint GetId() const;

    private:
        GLuint mId = 0;
    };   
}