//
// Created by hustlx on 2022/9/30.
//

#pragma once

#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#define GLEW_STATIC
#include <GL/glew.h>  // 必须在glfw之前
#include <iostream>


#define ASSERT(x) if((!x)) raise(SIGABRT);
// marco to print debug message when error occurred
#define glCall(x) ClearError();\
                  x;\
                  ASSERT(LogCall(__FILE__, #x, __LINE__))


void ClearError();
void CheckError();
bool LogCall(const char* file, const char* function, int line);

class VertexArray;
class IndexBuffer;
class Shader;

class Renderer {
public:
    void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const;

    void clear() const;
};


#endif //OPENGL_RENDERER_H
