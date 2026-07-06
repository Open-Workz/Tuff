#include "gl_mesh.h"

#include <cstddef>
#include <utility>

namespace OpenGL {
    Mesh::~Mesh() {
        Destroy();
    }

    Mesh::Mesh(Mesh&& other) noexcept {
        mVertices = std::move(other.mVertices);
        mIndices = std::move(other.mIndices);

        mVao = std::move(other.mVao);
        mVbo = std::move(other.mVbo);
        mEbo = std::move(other.mEbo);

        mIndexCount = other.mIndexCount;
        other.mIndexCount = 0;
    }

    Mesh& Mesh::operator=(Mesh&& other) noexcept {
        if (this != &other) {
            Destroy();

            mVertices = std::move(other.mVertices);
            mIndices = std::move(other.mIndices);

            mVao = std::move(other.mVao);
            mVbo = std::move(other.mVbo);
            mEbo = std::move(other.mEbo);

            mIndexCount = other.mIndexCount;
            other.mIndexCount = 0;
        }

        return *this;
    }

    void Mesh::SetData(const std::vector<Geometry::Vertex>& vertices, const std::vector<uint32_t>& indices) {
        mVertices = vertices;
        mIndices = indices;
    }

    const std::vector<Geometry::Vertex>& Mesh::GetVertices() const {
        return mVertices;
    }

    void Mesh::Upload() {
        mIndexCount = static_cast<GLsizei>(mIndices.size());

        if (!mVao.IsValid()) {
            mVao.Create();
            mVao.Bind();

            mVbo.Create(
                mVertices.data(),
                mVertices.size() * sizeof(Geometry::Vertex)
            );

            mEbo.Create(
                mIndices.data(),
                mIndices.size() * sizeof(uint32_t),
                mIndexCount
            );

            mVao.AddAttribute(
                0,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Geometry::Vertex),
                reinterpret_cast<void*>(offsetof(Geometry::Vertex, Position))
            );

            mVao.AddAttribute(
                1,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Geometry::Vertex),
                reinterpret_cast<void*>(offsetof(Geometry::Vertex, Normal))
            );

            mVao.AddAttribute(
                2,
                2,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Geometry::Vertex),
                reinterpret_cast<void*>(offsetof(Geometry::Vertex, TexCoords))
            );

            mVao.Unbind();
            return;
        }

        mVao.Bind();

        mVbo.SetData(
            mVertices.data(),
            mVertices.size() * sizeof(Geometry::Vertex)
        );

        mEbo.SetData(
            mIndices.data(),
            mIndices.size() * sizeof(uint32_t),
            mIndexCount
        );

        mVao.Unbind();
    }

    void Mesh::Destroy() {
        mEbo.Destroy();
        mVbo.Destroy();
        mVao.Destroy();

        mIndexCount = 0;
    }

    void Mesh::Clear() {
        mVertices.clear();
        mIndices.clear();

        mVertices.shrink_to_fit();
        mIndices.shrink_to_fit();
    }

    void Mesh::Draw() const {
        if (!IsUploaded())
            return;

        mVao.Bind();
        glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, nullptr);
        mVao.Unbind();
    }

    bool Mesh::IsUploaded() const {
        return mVao.IsValid()
            && mVbo.IsValid()
            && mEbo.IsValid()
            && mIndexCount > 0;
    }
}
