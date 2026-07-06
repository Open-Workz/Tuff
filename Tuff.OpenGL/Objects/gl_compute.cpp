#include "gl_compute.h"

#include <fstream>
#include <sstream>

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "../../Tuff.Core/Logger/Logger.h"

namespace OpenGL {
	bool Compute::Load(const std::string& path) {
		std::string source;
		if (!ReadFile(path, source)) { return false; }
		GLuint compute = Compile(GL_COMPUTE_SHADER, source, path);
		if (compute == 0) { return false; }
		mProgram = glCreateProgram();
		glAttachShader(mProgram, compute);
		glLinkProgram(mProgram);
		glDeleteShader(compute);
		GLint success = 0;
		glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
		if (!success) {
			GLint length = 0;
			glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &length);
			std::string log;
			log.resize(length);
			glGetProgramInfoLog(mProgram, length, nullptr, log.data());
			Tuff::Core::Logger::Error("OpenGL::Compute::Load", "Compute shader link failed:\n", log);
			glDeleteProgram(mProgram);
			mProgram = 0;
			return false;
		}
		return true;
	}

	void Compute::Bind() const {
		glUseProgram(mProgram);
	}

	void Compute::Dispatch(int groupsX, int groupsY, int groupsZ) const
	{
		glDispatchCompute(groupsX, groupsY, groupsZ);
		glMemoryBarrier(GL_ALL_BARRIER_BITS); // suspect?
	}

	void Compute::Unbind() const {
		glUseProgram(0);
	}

	void Compute::SetInt(const std::string& name, int value) {
		GLint location = glGetUniformLocation(mProgram, name.c_str());
		if (location == -1) { return; }
		glUniform1i(location, value);
	}

	void Compute::SetFloat(const std::string& name, float value) {
		GLint location = glGetUniformLocation(mProgram, name.c_str());
		if (location == -1) { return; }
		glUniform1f(location, value);
	}

	void Compute::SetVec3(const std::string& name, glm::vec3 values) {
		GLint location = glGetUniformLocation(mProgram, name.c_str());
		if (location == -1) { return; }
		glUniform3f(location, values.x, values.y, values.z);
	}

	void Compute::SetVec4(const std::string& name, glm::vec4 values) {
		GLint location = glGetUniformLocation(mProgram, name.c_str());
		if (location == -1) { return; }
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void Compute::SetMat4(const std::string& name, const glm::mat4& matrix) {
		GLint location = glGetUniformLocation(mProgram, name.c_str());
		if (location == -1) { return; }
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Compute::SetBool(const std::string& name, bool enabled)
	{
		GLint location = glGetUniformLocation(mProgram, name.c_str());
		if (location == -1) { return; }
		glUniform1i(location, enabled ? 1 : 0);
	}

	GLuint Compute::GetProgram() const {
		return mProgram;
	}

	bool Compute::ReadFile(const std::string& path, std::string& outSource) {
		std::ifstream file(path);
		if (!file.is_open()) {
			Tuff::Core::Logger::Error("OpenGL::Compute::ReadFile", "Failed to open compute shader file: ", path);
			return false;
		}
		std::stringstream stream;
		stream << file.rdbuf();
		outSource = stream.str();
		return true;
	}

	GLuint Compute::Compile(GLenum type, const std::string& source, const std::string& path) {
		GLuint shader = glCreateShader(type);
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
			Tuff::Core::Logger::Error("OpenGL::Compute::Compile", "Compute shader compile failed: ", path, "\n", log);
			glDeleteShader(shader);
			return 0;
		}
		return shader;
	}
}
