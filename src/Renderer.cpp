//
// Created by hustlx on 2022/9/30.
//

#include "Renderer.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

void CheckError() {
    while(GLenum error = glGetError()) {
        std::cout << "[OpenGL Error]: " << error << '\n';
    }
}

void ClearError() {
    while(glGetError() != GL_NO_ERROR);
}

bool LogCall(const char* file, const char* function, int line) {
    while(GLenum error = glGetError()) {
        std::cout << "[OpenGL Error]" << "\nfile: " << file << "\nfunction: " << function << "\nerror code: " << error
                  << std::hex << "\nerror code(hex): " << error << '\n';
        return false;
    }
    return true;
}

void Renderer::draw(const VertexArray &vertexArray, const IndexBuffer &indexBuffer, const Shader &shader) const {
    vertexArray.bind();
    indexBuffer.bind();
    shader.bind();
    glCall(glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear() const {
    glCall(glClear(GL_COLOR_BUFFER_BIT));
}
