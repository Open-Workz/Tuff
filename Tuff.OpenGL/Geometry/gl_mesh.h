#pragma once

#include <vector>
#include <cstdint>

#include <GL/glew.h>

#include "../Geometry/gl_vertex.h"
#include "../Objects/gl_vertex_array.h"
#include "../Objects/gl_vertex_buffer.h"
#include "../Objects/gl_index_buffer.h"

namespace OpenGL {
    struct Mesh {
        Mesh() = default;
        ~Mesh();

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        Mesh(Mesh&& other) noexcept;
        Mesh& operator=(Mesh&& other) noexcept;

        void SetData(const std::vector<Geometry::Vertex>& vertices, const std::vector<uint32_t>& indices);
        const std::vector<Geometry::Vertex>& GetVertices() const;
        void Upload();
        void Destroy();
        void Clear();
        void Draw() const;

        bool IsUploaded() const;

    private:
        std::vector<Geometry::Vertex> mVertices;
        std::vector<uint32_t> mIndices;

        VertexArray mVao;
        VertexBuffer mVbo;
        IndexBuffer mEbo;

        GLsizei mIndexCount = 0;
    };   
}
