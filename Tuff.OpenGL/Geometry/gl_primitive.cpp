#include "gl_primitive.h"

#include <algorithm>
#include <ext/scalar_constants.hpp>

namespace OpenGL::Primitive {
    Mesh Quad(float width, float height) {
        float hw = width * 0.5f;
        float hh = height * 0.5f;

        std::vector<Geometry::Vertex> vertices =
        {
            {{-hw, -hh, 0.0f}, {0, 0, 1}, {0, 0}},
            {{ hw, -hh, 0.0f}, {0, 0, 1}, {1, 0}},
            {{ hw,  hh, 0.0f}, {0, 0, 1}, {1, 1}},
            {{-hw,  hh, 0.0f}, {0, 0, 1}, {0, 1}}
        };

        std::vector<uint32_t> indices =
        {
            0, 1, 2,
            0, 2, 3
        };

        Mesh mesh;
        mesh.SetData(vertices, indices);
        mesh.Upload();

        return mesh;
    }

    Mesh Plane(float width, float depth) {
        std::vector<Geometry::Vertex> vertices =
        {
            {{-width, 0.0f, -depth}, {0, 1, 0}, {0, 0}},
            {{ width, 0.0f, -depth}, {0, 1, 0}, {1, 0}},
            {{ width, 0.0f,  depth}, {0, 1, 0}, {1, 1}},
            {{-width, 0.0f,  depth}, {0, 1, 0}, {0, 1}}
        };

        std::vector<uint32_t> indices =
        {
            0, 2, 1,
            0, 3, 2
        };

        Mesh mesh;
        mesh.SetData(vertices, indices);
        mesh.Upload();

        return mesh;
    }

    Mesh Cube(float width, float height, float depth) {
        float w = width  * 0.5f;
        float h = height * 0.5f;
        float d = depth  * 0.5f;
        std::vector<Geometry::Vertex> vertices =
        {
            // Front +Z
            {{-w, -h,  d}, {0, 0, 1}, {0, 0}},
            {{ w, -h,  d}, {0, 0, 1}, {1, 0}},
            {{ w,  h,  d}, {0, 0, 1}, {1, 1}},
            {{-w,  h,  d}, {0, 0, 1}, {0, 1}},

            // Back -Z
            {{ w, -h, -d}, {0, 0, -1}, {0, 0}},
            {{-w, -h, -d}, {0, 0, -1}, {1, 0}},
            {{-w,  h, -d}, {0, 0, -1}, {1, 1}},
            {{ w,  h, -d}, {0, 0, -1}, {0, 1}},

            // Left -X
            {{-w, -h, -d}, {-1, 0, 0}, {0, 0}},
            {{-w, -h,  d}, {-1, 0, 0}, {1, 0}},
            {{-w,  h,  d}, {-1, 0, 0}, {1, 1}},
            {{-w,  h, -d}, {-1, 0, 0}, {0, 1}},

            // Right +X
            {{ w, -h,  d}, {1, 0, 0}, {0, 0}},
            {{ w, -h, -d}, {1, 0, 0}, {1, 0}},
            {{ w,  h, -d}, {1, 0, 0}, {1, 1}},
            {{ w,  h,  d}, {1, 0, 0}, {0, 1}},

            // Top +Y
            {{-w,  h,  d}, {0, 1, 0}, {0, 0}},
            {{ w,  h,  d}, {0, 1, 0}, {1, 0}},
            {{ w,  h, -d}, {0, 1, 0}, {1, 1}},
            {{-w,  h, -d}, {0, 1, 0}, {0, 1}},

            // Bottom -Y
            {{-w, -h, -d}, {0, -1, 0}, {0, 0}},
            {{ w, -h, -d}, {0, -1, 0}, {1, 0}},
            {{ w, -h,  d}, {0, -1, 0}, {1, 1}},
            {{-w, -h,  d}, {0, -1, 0}, {0, 1}},
        };

        std::vector<uint32_t> indices =
        {
            0,  1,  2,  0,  2,  3,
            4,  5,  6,  4,  6,  7,
            8,  9, 10,  8, 10, 11,
           12, 13, 14, 12, 14, 15,
           16, 17, 18, 16, 18, 19,
           20, 21, 22, 20, 22, 23
       };

        Mesh mesh;
        mesh.SetData(vertices, indices);
        mesh.Upload();
        return mesh;
    }

    Mesh QuadSphere(float radius, int resolution)
    {
        std::vector<Geometry::Vertex> vertices;
        std::vector<uint32_t> indices;

        resolution = std::max(resolution, 2);

        auto buildFace = [&](const glm::vec3& localUp)
        {
            glm::vec3 axisA(localUp.y, localUp.z, localUp.x);
            glm::vec3 axisB = glm::cross(localUp, axisA);

            auto makeVertex = [&](int x, int y) -> Geometry::Vertex
            {
                glm::vec2 percent((float)x / (float)(resolution - 1), (float)y / (float)(resolution - 1));

                glm::vec3 pointOnCube =
                    localUp +
                    (percent.x - 0.5f) * 2.0f * axisA +
                    (percent.y - 0.5f) * 2.0f * axisB;

                glm::vec3 normal = glm::normalize(pointOnCube);

                float u = 0.5f - atan2(normal.z, normal.x) / (2.0f * glm::pi<float>());
                float v = 0.5f - asin(normal.y) / glm::pi<float>();

                Geometry::Vertex vertex;
                vertex.Position = normal * radius;
                vertex.Normal = normal;
                vertex.TexCoords = glm::vec2(u, v);
                return vertex;
            };

            for (int y = 0; y < resolution - 1; y++)
            {
                for (int x = 0; x < resolution - 1; x++)
                {
                    Geometry::Vertex v00 = makeVertex(x,     y);
                    Geometry::Vertex v10 = makeVertex(x + 1, y);
                    Geometry::Vertex v01 = makeVertex(x,     y + 1);
                    Geometry::Vertex v11 = makeVertex(x + 1, y + 1);

                    float minU = std::min(std::min(v00.TexCoords.x, v10.TexCoords.x), std::min(v01.TexCoords.x, v11.TexCoords.x));
                    float maxU = std::max(std::max(v00.TexCoords.x, v10.TexCoords.x), std::max(v01.TexCoords.x, v11.TexCoords.x));

                    if (maxU - minU > 0.5f)
                    {
                        if (v00.TexCoords.x < 0.5f) v00.TexCoords.x += 1.0f;
                        if (v10.TexCoords.x < 0.5f) v10.TexCoords.x += 1.0f;
                        if (v01.TexCoords.x < 0.5f) v01.TexCoords.x += 1.0f;
                        if (v11.TexCoords.x < 0.5f) v11.TexCoords.x += 1.0f;
                    }

                    uint32_t i = static_cast<uint32_t>(vertices.size());

                    vertices.push_back(v00);
                    vertices.push_back(v10);
                    vertices.push_back(v01);
                    vertices.push_back(v11);

                    indices.push_back(i + 0);
                    indices.push_back(i + 3);
                    indices.push_back(i + 2);

                    indices.push_back(i + 0);
                    indices.push_back(i + 1);
                    indices.push_back(i + 3);
                }
            }
        };

        buildFace(glm::vec3( 1.0f,  0.0f,  0.0f));
        buildFace(glm::vec3(-1.0f,  0.0f,  0.0f));
        buildFace(glm::vec3( 0.0f,  1.0f,  0.0f));
        buildFace(glm::vec3( 0.0f, -1.0f,  0.0f));
        buildFace(glm::vec3( 0.0f,  0.0f,  1.0f));
        buildFace(glm::vec3( 0.0f,  0.0f, -1.0f));

        Mesh mesh;
        mesh.SetData(vertices, indices);
        mesh.Upload();
        return mesh;
    }
}
