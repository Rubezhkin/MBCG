#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include <glm/glm.hpp>
#include <fstream>
#include <sstream>

class Shader
{
public:
    Shader() {
        std::string vertex_shader_code = loadShaderFile("Vshader.txt");
        std::string fragment_shader_code = loadShaderFile("Fshader.txt");

        const char* vertex_shader = vertex_shader_code.c_str();
        const char* fragment_shader = fragment_shader_code.c_str();
        GLuint vs = compileShader(GL_VERTEX_SHADER, vertex_shader);
        GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragment_shader);

       _shaderId = glCreateProgram();
        glAttachShader(_shaderId, vs);
        glAttachShader(_shaderId, fs);
        glLinkProgram(_shaderId);

       // glDeleteShader(vs);
       // glDeleteShader(fs);
    }

    void bind() const {
        glUseProgram(_shaderId);
    }

    void setInt(const char* name, int value) const {
        glUniform1i(glGetUniformLocation(_shaderId, name), value);
    }

    void setFloat(const char* name, float value) const {
        glUniform1f(glGetUniformLocation(_shaderId, name), value);
    }

    void setVec2(const char* name, const glm::vec2& value) const {
        glUniform2fv(glGetUniformLocation(_shaderId, name), 1, &value[0]);
    }

    void setVec3(const char* name, const glm::vec3& value) const {
        glUniform3fv(glGetUniformLocation(_shaderId, name), 1, &value[0]);
    }

    void setVec4(const char* name, const glm::vec4& value) const {
        glUniform4fv(glGetUniformLocation(_shaderId, name), 1, &value[0]);
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
    GLuint compileShader(GLenum type, const char* source) const {
        GLuint shader = glCreateShader(type);
        const GLchar* src = source;
        glShaderSource(shader, 1, &src, NULL);
        glCompileShader(shader);

        return shader;
    }

	unsigned int _shaderId;
};


