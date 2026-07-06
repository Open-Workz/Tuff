#include "AssetPath.h"

namespace Tuff::Core::AssetPath {
    std::string Shader(const std::string& file)
    {
        return Root("Shaders", file);
    }

    std::string Texture(const std::string& file)
    {
        return Root("Textures", file);
    }

    std::string Model(const std::string& file)
    {
        return Root("Models", file);
    }
    
    std::string Audio(const std::string& file)
    {
        return Root("Audio", file);
    }
    
    static std::string Root(const std::string& folder, const std::string& file) {
        return std::string(ASSET_ROOT) + "/" + folder + "/" + file;
    }
}