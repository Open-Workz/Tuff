#include "gl_vertex_array.h"

namespace OpenGL {
    
    VertexArray::~VertexArray() {
        Destroy();
    }

    VertexArray::VertexArray(VertexArray&& other) noexcept {
        mId = other.mId;
        mSSBO = other.mSSBO;

        other.mId = 0;
        other.mSSBO = 0;
    }

    VertexArray& VertexArray::operator=(VertexArray&& other) noexcept {
        if (this != &other) {
            Destroy();

            mId = other.mId;
            mSSBO = other.mSSBO;

            other.mId = 0;
            other.mSSBO = 0;
        }

        return *this;
    }
    
    void VertexArray::Create() {
        Destroy();

        glCreateVertexArrays(1, &mId);
        glCreateBuffers(1, &mSSBO);
    }

    void VertexArray::Bind() const {
        glBindVertexArray(mId);
    }

    void VertexArray::Unbind() const {
        glBindVertexArray(0);
    }

    void VertexArray::Destroy() {
        if (mSSBO != 0)
        {
            glDeleteBuffers(1, &mSSBO);
            mSSBO = 0;
        }

        if (mId != 0)
        {
            glDeleteVertexArrays(1, &mId);
            mId = 0;
        }
    }

    void VertexArray::AddAttribute(GLuint index, GLint count, GLenum type, GLboolean normalized, GLsizei stride, const void* offset) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, count, type, normalized, stride, offset);
    }

    void VertexArray::SetSSBOData(const std::vector<int>& data) {
        if (mSSBO == 0) {
            glCreateBuffers(1, &mSSBO);
        }

        glNamedBufferData(
            mSSBO,
            data.size() * sizeof(int),
            data.data(),
            GL_STATIC_DRAW
        );
    }

    void VertexArray::BindSSBO(GLuint binding) const {
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, mSSBO);
    }

    GLuint VertexArray::GetId() const {
        return mId;
    }

    bool VertexArray::IsValid() const {
        return mId != 0;
    }

}