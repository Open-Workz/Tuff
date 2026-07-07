#include "Sandbox.h"

#include "Tuff.Core/Asset/AssetPath.h"
#include "Tuff.Core/Editor/Camera/Camera.h"
#include "Tuff.Core/Editor/Grid/Grid.h"
#include "Tuff.Core/Math/Transform.h"
#include "Tuff.OpenGL/Commands/gl_commands.h"
#include "Tuff.OpenGL/Geometry/gl_mesh.h"
#include "Tuff.OpenGL/Geometry/gl_primitive.h"
#include "Tuff.OpenGL/Resource/gl_resource_manager.h"

namespace Sandbox {
    namespace {
        OpenGL::Mesh gMesh;
        Tuff::Core::Math::Transform gTransform;
    }
    
    void Init() {
        Tuff::Core::Editor::Camera::Init();
        Tuff::Core::Editor::Grid::Init();
        
        OpenGL::ResourceManager::AddShader(
            "basic",
            Tuff::Core::AssetPath::Shader("Core/basic.vert"),
            Tuff::Core::AssetPath::Shader("Core/basic.frag")
        );
        
        gMesh = OpenGL::Primitive::Cube(1.f);
    }

    void Input() {
    }

    void Update() {
        Tuff::Core::Editor::Camera::Update();
    }

    void Render() {
        Tuff::Core::Editor::Grid::Render();
        OpenGL::Commands::BindShader("basic");
        OpenGL::Commands::SetUniformMat4("uModel", gTransform.GetMatrix());
        OpenGL::Commands::SetUniformMat4("uView", Tuff::Core::Editor::Camera::GetViewMatrix());
        OpenGL::Commands::SetUniformMat4("uProjection", Tuff::Core::Editor::Camera::GetProjectionMatrix());
        gMesh.Draw();
    }
}
