#pragma once

#include <string>

#ifndef ASSET_ROOT
#define ASSET_ROOT "../Assets"
#endif

namespace Tuff::Core::AssetPath {
    std::string Shader(const std::string& file);
    std::string Texture(const std::string& file);
    std::string Model(const std::string& file);
    std::string Audio(const std::string& file);
    std::string Root(const std::string& folder, const std::string& file);
}
