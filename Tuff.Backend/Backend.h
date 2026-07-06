#pragma once

#include <string>

#include "../Tuff.Core/Common/Common.h"

namespace Tuff::Backend {
    bool Init(API api, int width, int height, const std::string& title);
    void BeginFrame();
    void EndFrame();
    
    void* GetWindowPtr();
    
    void Shutdown();
}