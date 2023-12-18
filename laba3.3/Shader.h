#pragma once
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	GLuint m_shaderId;
	Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path) {
		std::string vertex_shader_code = loadShaderFile(vertex_shader_path);
		std::string fragment_shader_code = loadShaderFile(fragment_shader_path);

		const char* vertex_shader = vertex_shader_code.c_str();
		const char* fragment_shader = fragment_shader_code.c_str();

		GLuint vs = compileShader(GL_VERTEX_SHADER, vertex_shader);
		GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragment_shader);
		m_shaderId = glCreateProgram();
		
		glAttachShader(m_shaderId, vs);
		glAttachShader(m_shaderId, fs);
		glLinkProgram(m_shaderId);

		//glDeleteShader(vs);
		//glDeleteShader(fs);
	}


	void bind() const
	{
		glUseProgram(m_shaderId);
	}

	void release() const
	{
		glUseProgram(0);
	}

	void setInt(const std::string& name, int value)
	{
		glUniform1i(glGetUniformLocation(m_shaderId, name.c_str()), value);
	}

	void setFloat(const std::string& name, float value)
	{
		glUniform1f(glGetUniformLocation(m_shaderId, name.c_str()), value);
	}

	void setVec2(const std::string& name, const glm::vec2& value)
	{
		glUniform2fv(glGetUniformLocation(m_shaderId, name.c_str()), 1, glm::value_ptr(value));
	}

	void setVec3(const std::string& name, const glm::vec3& value)
	{
		glUniform3fv(glGetUniformLocation(m_shaderId, name.c_str()), 1, glm::value_ptr(value));
	}

	void setVec4(const std::string& name, const glm::vec4& value)
	{
		glUniform4fv(glGetUniformLocation(m_shaderId, name.c_str()), 1, glm::value_ptr(value));
	}

private:


	std::string loadShaderFile(const std::string& shaderPath) {
		std::ifstream shaderFile(shaderPath);
		if (!shaderFile.is_open()) {
			std::cerr << "Error: Failed to open shader file: " << shaderPath << std::endl;
			return "";
		}

		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();

		return shaderStream.str();
	}
	GLuint linkProgram(GLuint vs, GLuint fs)
	{

		GLuint shader_programme = glCreateProgram();
		glAttachShader(shader_programme, vs);
		glAttachShader(shader_programme, fs);
		glLinkProgram(shader_programme);
		glUseProgram(shader_programme);
		return shader_programme;
	}
	GLuint compileShader(GLenum type, const char* source) const {
		GLuint shader = glCreateShader(type);
		const GLchar* src = source;
		glShaderSource(shader, 1, &src, NULL);
		glCompileShader(shader);

		return shader;
	}

	unsigned int _shaderId;
};
