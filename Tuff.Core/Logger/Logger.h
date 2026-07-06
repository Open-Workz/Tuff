#pragma once

#include <iostream>

namespace Tuff::Core::Logger {
    enum class Level { Debug = 0, Info, Warn, Error, Off };

    inline Level CurrentLevel = Level::Debug;

    inline constexpr const char* Reset  = "\033[0m";
    inline constexpr const char* Green  = "\033[32m";
    inline constexpr const char* Yellow = "\033[33m";
    inline constexpr const char* Red    = "\033[31m";
    inline constexpr const char* Cyan   = "\033[36m";
    inline constexpr const char* Gray   = "\033[90m";
    inline constexpr const char* Blue   = "\033[34m";

    inline void SetLevel(Level level) { CurrentLevel = level; }

    inline bool ShouldLog(Level level) {
        return static_cast<int>(level) >= static_cast<int>(CurrentLevel);
    }

    template<typename Stream, typename... Args>
    void Write(Stream& stream, const char* levelColor, const char* levelName, const char* tag, Args&&... args) {
        stream << levelColor << "[" << levelName << "] " << Reset;
        stream << Blue << "[" << tag << "] " << Reset;
        ((stream << args), ...);
        stream << '\n';
    }

    template<typename... Args>
    void Info(const char* tag, Args&&... args) {
        if (!ShouldLog(Level::Info)) return;
        Write(std::cout, Green, "INFO", tag, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Warn(const char* tag, Args&&... args) {
        if (!ShouldLog(Level::Warn)) return;
        Write(std::cout, Yellow, "WARN", tag, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Error(const char* tag, Args&&... args) {
        if (!ShouldLog(Level::Error)) return;
        Write(std::cerr, Red, "ERROR", tag, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Debug(const char* tag, Args&&... args) {
        if (!ShouldLog(Level::Debug)) return;
        Write(std::cerr, Cyan, "DEBUG", tag, std::forward<Args>(args)...);
    }
}