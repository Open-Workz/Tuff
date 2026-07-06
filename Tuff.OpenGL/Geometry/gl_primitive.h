#pragma once

#include "../Geometry/gl_mesh.h"

namespace OpenGL::Primitive {
    Mesh Quad(float width = 1.f, float height = 1.f);
    Mesh Plane(float width = 1.f, float length = 1.f);
    Mesh Cube(float width = 1.f, float height = 1.f, float depth = 1.f);
    Mesh QuadSphere(float radius = 1.0f, int resolution = 16);
}