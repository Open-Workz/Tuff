#pragma once

#include <GL/glew.h>

namespace OpenGL::Common {
    static int ChannelsFromInternalFormat3D(GLenum internalFormat) {
        switch (internalFormat) {
            case GL_R8:
            case GL_R16F:
            case GL_R32F:
                return 1;

            case GL_RG8:
            case GL_RG16F:
            case GL_RG32F:
                return 2;

            case GL_RGB8:
            case GL_RGB16F:
            case GL_RGB32F:
                return 3;

            case GL_RGBA8:
            case GL_RGBA16F:
            case GL_RGBA32F:
                return 4;

            default:
                return 0;
        }
    }

    static int ChannelsFromInternalFormat2D(GLenum internalFormat) {
        switch (internalFormat) {
            case GL_R8:
            case GL_R16F:
            case GL_R32F:
                return 1;

            case GL_RG8:
            case GL_RG16F:
            case GL_RG32F:
                return 2;

            case GL_RGB8:
            case GL_RGB16F:
            case GL_RGB32F:
                return 3;

            case GL_RGBA8:
            case GL_RGBA16F:
            case GL_RGBA32F:
                return 4;

            default:
                return 0;
        }
    }

    static GLenum DataFormatFromChannels2D(int channels) {
        switch (channels) {
            case 1: return GL_RED;
            case 2: return GL_RG;
            case 3: return GL_RGB;
            case 4: return GL_RGBA;
            default: return GL_RGBA;
        }
    }

    static GLenum InternalFormatFromChannels2D(int channels) {
        switch (channels) {
            case 1: return GL_R8;
            case 2: return GL_RG8;
            case 3: return GL_RGB8;
            case 4: return GL_RGBA8;
            default: return GL_RGBA8;
        }
    }
}