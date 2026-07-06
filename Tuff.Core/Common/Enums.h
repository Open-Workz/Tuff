#pragma once

#include <cstdint>

enum class API : std::uint8_t {
    OPENGL
};

enum class WindowMode : uint8_t {
    WINDOWED,
    FULLSCREEN
};

enum class WindowAlignment : uint8_t {
    CENTER,
    CENTER_HORIZONTAL,
    CENTER_VERTICAL
};