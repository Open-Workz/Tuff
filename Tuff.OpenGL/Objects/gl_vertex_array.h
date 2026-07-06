#pragma once

#include <GL/glew.h>
#include <vector>

namespace OpenGL {
    struct VertexArray {
        VertexArray() = default;
        ~VertexArray();

        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(const VertexArray&) = delete;

        VertexArray(VertexArray&& other) noexcept;
        VertexArray& operator=(VertexArray&& other) noexcept;

        void Create();
        void Bind() const;
        void Unbind() const;
        void Destroy();

        void AddAttribute(
            GLuint index,
            GLint count,
            GLenum type,
            GLboolean normalized,
            GLsizei stride,
            const void* offset
        );

        void SetSSBOData(const std::vector<int>& data);
        void BindSSBO(GLuint binding = 0) const;

        GLuint GetId() const;
        bool IsValid() const;

    private:
        GLuint mId = 0;
        GLuint mSSBO = 0;
    };   
}