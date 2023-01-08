// @author: lx
// @time: 2022/10/1
// @brief: 

#pragma once
#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"


enum ShaderType {
    None = 0x0,
    VertexShader = 0x1,
    FragmentShader = 0x2
};


class Shader {
public:
    explicit Shader(std::string  vertexShaderFile, std::string  fragmentShaderFile);
    ~Shader();

    void bind() const;
    void unbind() const;

    void setUniform4f(const std::string& name, float, float, float, float);
    void setUniform1i(const std::string& name, int i1);
    void setUniformMat4f(const std::string& name, const glm::mat4& matrix);
    void setUniform1iv(const std::string& name, int count, int* value);

    inline unsigned getId() const { return m_renderer_id; }

private:
    unsigned m_renderer_id;
    std::string m_vs_file, m_fs_file;

    unsigned getUniformLocation(const std::string& name) const;
    static std::string parseShader(const std::string& fileName);
    void createShader(const std::string& shaderSource, ShaderType shaderType);
    unsigned compileShader(const std::string& shaderSource, unsigned type);
};

#endif //OPENGL_SHADER_H
