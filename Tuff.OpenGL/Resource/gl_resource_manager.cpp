#include "gl_resource_manager.h"

#include <unordered_map>

#include "../../Tuff.Core/Asset/AssetPath.h"
#include "../Objects/gl_shader.h"
#include "../Objects/gl_texture2D.h"

namespace OpenGL::ResourceManager {
    namespace {
        std::unordered_map<std::string, Shader> gShaders;
        std::unordered_map<std::string, Texture2D> gTextures2D;
    }
    bool AddShader(const std::string& name, const std::string& vert, const std::string& frag) {
        Shader shader;
        if (!shader.Load(vert, frag)) {
            return false;
        }
        gShaders[name] = shader;
        return true;
    }

    void RemoveShader(const std::string& name) {
        if (gShaders.contains(name)) {
            gShaders.erase(name);
        }
    }

    Shader* GetShaderPointer(const std::string& name) {
        if (!gShaders.contains(name)) {
            return nullptr;
        }
        return &gShaders[name];
    }

    bool AddTexture2D(const std::string& name, const std::string& texture) {
        Texture2D texture2D;
        if (!texture2D.Load(texture)) {
            return false;
        }
        gTextures2D[name] = std::move(texture2D);
        return true;
    }

    void RemoveTexture2D(const std::string& name) {
        if (gTextures2D.contains(name)) {
            gTextures2D.erase(name);
        }
    }

    Texture2D* GetTexture2DPointer(const std::string& name) {
        if (!gTextures2D.contains(name)) {
            return nullptr;
        }
        return &gTextures2D[name];
    }

    void Destroy() {
    }
}
