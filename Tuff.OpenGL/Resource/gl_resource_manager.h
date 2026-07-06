#pragma once

#include <string>

namespace OpenGL {
    struct Shader;
    struct Texture2D;
}

namespace OpenGL::ResourceManager {
    bool AddShader(const std::string& name, const std::string& vert, const std::string& frag);
    void RemoveShader(const std::string& name);
    Shader* GetShaderPointer(const std::string& name);
    
    bool AddTexture2D(const std::string& name, const std::string& texture);
    void RemoveTexture2D(const std::string& name);
    Texture2D* GetTexture2DPointer(const std::string& name);
    
    void Destroy();
}
