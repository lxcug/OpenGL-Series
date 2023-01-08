#include "Shader.h"

#include "Renderer.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>


Shader::Shader(std::string vertexShaderFile, std::string fragmentShaderFile):
        m_renderer_id(0), m_vs_file(std::move(vertexShaderFile)), m_fs_file(std::move(fragmentShaderFile)) {
    std::string vertexShaderString = parseShader(m_vs_file);
    std::string fragmentShaderString = parseShader(m_fs_file);

    m_renderer_id = glCreateProgram();
    createShader(vertexShaderString, VertexShader);
    createShader(fragmentShaderString, FragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(m_renderer_id);
}

void Shader::bind() const {
    glCall(glUseProgram(m_renderer_id));
}

void Shader::unbind() const {
    glCall(glUseProgram(0));
}

unsigned Shader::getUniformLocation(const std::string &name) const {
    glCall(int location = glGetUniformLocation(m_renderer_id, name.c_str()));
    if(location == -1) {
        std::cout << "Warning: uniform " << name << " doesn't exist\n";
    }
    return location;
}

std::string Shader::parseShader(const std::string& fileName) {
    std::ifstream file(fileName, std::ios::in);
    if(!file.is_open()) {
        std::cout << "Failed to open " << fileName << '\n';
        return "";
    }
    std::string line;
    std::stringstream stringStream;
    while(std::getline(file, line)) {
        stringStream << line << '\n';
    }
    return stringStream.str();
}

void Shader::createShader(const std::string& shaderSource, ShaderType shaderType) {
    unsigned type;
    switch (shaderType) {
        case VertexShader : {
            type = GL_VERTEX_SHADER;
            break;
        }
        case FragmentShader : {
            type = GL_FRAGMENT_SHADER;
            break;
        }
        case None :
            ASSERT(false);
    }

    unsigned shader = compileShader(shaderSource, type);
    glCall(glAttachShader(m_renderer_id, shader));
    glCall(glLinkProgram(m_renderer_id));
    glCall(glValidateProgram(m_renderer_id));
    glCall(glDeleteShader(shader))
}

unsigned Shader::compileShader(const std::string& shaderSource, unsigned type) {
    unsigned id = glCreateShader(type);
    const char* src = shaderSource.c_str();
    glCall(glShaderSource(id, 1, &src, nullptr));
    glCall(glCompileShader(id));

    int result;
    glCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

    // error handling
    if(result == GL_FALSE) {
        int length;
        glCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char message[length];
        glCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader") << std::endl;
        std::cout << message << std::endl;
        glCall(glDeleteShader(id));
        return 0;
    }
    return id;
}

void Shader::setUniform4f(const std::string &name, float f1, float f2, float f3, float f4) {
    glCall(glUniform4f(getUniformLocation(name), f1, f2, f3, f4));
}

void Shader::setUniform1i(const std::string &name, int i1) {
    glCall(glUniform1i(getUniformLocation(name), i1));
}

void Shader::setUniformMat4f(const std::string &name, const glm::mat4& matrix) {
     glCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::setUniform1iv(const std::string &name, int count, int *value) {
    glCall(glUniform1iv(getUniformLocation(name), count, value));
}
