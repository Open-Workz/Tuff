#include "gl_shader.h"

#include <filesystem>
#include <fstream>
#include <sstream>

#include "../../Tuff.Core/Logger/Logger.h"

namespace OpenGL {
	bool Shader::Load(const std::string& vertexPath, const std::string& fragmentPath) {
	    std::string vertexSource;
	    std::string fragmentSource;
	    if (!ReadFile(vertexPath, vertexSource)) { return false; }
	    if (!ReadFile(fragmentPath, fragmentSource)) { return false; }
	    GLuint vertexShader = Compile(GL_VERTEX_SHADER, vertexSource, vertexPath);
	    if (vertexShader == 0) { return false; }
	    GLuint fragmentShader = Compile(GL_FRAGMENT_SHADER, fragmentSource, fragmentPath);
	    if (fragmentShader == 0) {
	        glDeleteShader(vertexShader);
	        return false;
	    }
	    mProgram = glCreateProgram();
	    glAttachShader(mProgram, vertexShader);
	    glAttachShader(mProgram, fragmentShader);
	    glLinkProgram(mProgram);
	    glDeleteShader(vertexShader);
	    glDeleteShader(fragmentShader);
	    GLint success = 0;
	    glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
	    if (!success) {
	        GLint length = 0;
	        glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &length);
	        std::string log;
	        log.resize(length);
	        glGetProgramInfoLog(mProgram, length, nullptr, log.data());
	        Tuff::Core::Logger::Error("OpenGL::GLShader::Load", "Shader link failed:\n", log);
	        glDeleteProgram(mProgram);
	        mProgram = 0;
	        return false;
	    }
	    return true;
	}

	GLuint Shader::GetProgram() const {
		return mProgram;
	}

	bool Shader::ReadFile(const std::string& path, std::string& outSource) {
		std::filesystem::path file_path(path);
		std::filesystem::path folder = file_path.parent_path();
		
		std::ifstream file(file_path);
		if (!file.is_open()) {
			Tuff::Core::Logger::Error("OpenGL::Shader::ReadFile", "Failed to open shader file: ", path);
			return false;
		}
		
		std::stringstream output;
		std::string line;
		
		while (std::getline(file, line)) {
			if (line.rfind("#include", 0) == 0) {
				size_t firstQuote = line.find('"');
				size_t lastQuote = line.find_last_of('"');
				
				if (firstQuote == std::string::npos || lastQuote == firstQuote) {
					Tuff::Core::Logger::Error("OpenGL::Shader::ReadFile", "Invalid include: ", line);
					return false;
				}
				
				std::string includeFile = line.substr(firstQuote + 1, lastQuote - firstQuote - 1);
				std::filesystem::path includePath = folder / includeFile;
				
				std::string includeSource;
				if (!ReadFile(includePath.string(), includeSource)) {
					return false;
				}
				
				output << includeSource << "\n";
			} else {
				output << line << "\n";
			}
		}
		
		outSource = output.str();
		return true;
	}

	GLuint Shader::Compile(GLenum type, const std::string& source, const std::string& path) {
		const GLuint shader = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(shader, 1, &src, nullptr);
		glCompileShader(shader);
		GLint success = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLint length = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			std::string log;
			log.resize(length);
			glGetShaderInfoLog(shader, length, nullptr, log.data());
			Tuff::Core::Logger::Error("OpenGL::Shader::Compile", "Shader compile failed: ", path, "\n", log);
			glDeleteShader(shader);
			return 0;
		}
		return shader;
	}
}
