#include "Grid.h"

#include <GL/glew.h>

#include "../../Asset/AssetPath.h"
#include "../Camera/Camera.h"
#include "../../Tuff.OpenGL/Objects/gl_shader.h"
#include "../../Tuff.OpenGL/Commands/gl_commands.h"
#include "../../Tuff.OpenGL/Resource/gl_resource_manager.h"

namespace Tuff::Core::Editor::Grid {
    namespace {
        GLuint mVao = 0;
        float gGridSize = 10000.f;
        float gGridMinPixelBetweenCells = 4.f;
        float gGridCellSize = 0.1f;
        float gGridLodBias = 1.f;
        glm::vec4 gGridColorThin{1.f, 1.f, 1.f, 0.5f};
        glm::vec4 gGridColorThick{1.f, 1.f, 1.f, 0.5f};
    }
    
    bool Init() {
        glGenVertexArrays(1, &mVao);
        return OpenGL::ResourceManager::AddShader("grid", AssetPath::Shader("Editor/grid.vert"), AssetPath::Shader("Editor/grid.frag"));
    }

    void Update() {
        OpenGL::Commands::BindShader("grid");
        OpenGL::Commands::SetUniformMat4("uView", Camera::GetViewMatrix());
        OpenGL::Commands::SetUniformMat4("uProjection", Camera::GetProjectionMatrix());
        OpenGL::Commands::SetUniformVec3("uViewPosition", Camera::GetPosition());
        OpenGL::Commands::SetUniformFloat("uGridSize", gGridSize);
        OpenGL::Commands::SetUniformFloat("uGridMinPixelBetweenCells", gGridMinPixelBetweenCells);
        OpenGL::Commands::SetUniformFloat("uGridCellSize", gGridCellSize);
        OpenGL::Commands::SetUniformFloat("uGridLodBias", gGridLodBias);
        OpenGL::Commands::SetUniformVec4("uGridColorThin", gGridColorThin);
        OpenGL::Commands::SetUniformVec4("uGridColorThick", gGridColorThick);
        
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDepthMask(GL_FALSE);

        glBindVertexArray(mVao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);
        glDisable(GL_BLEND);
    }

    void ImGui() {
    }
}
