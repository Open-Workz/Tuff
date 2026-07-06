#pragma once

#include <string>

#include "../Common/Common.h"

namespace Tuff::Core::Platform {
    struct WindowSettings {
        std::string Title = "TuffFX";
        int Width = 1300;
        int Height = 900;
        bool VSync = false;
        WindowMode WindowMode = WindowMode::WINDOWED;
        WindowAlignment WindowAlignment = WindowAlignment::CENTER;
    };   
}