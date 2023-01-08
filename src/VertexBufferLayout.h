// @author: lx
// @time: 2022/10/1
// @brief: 

#pragma once

#ifndef OPENGL_VERTEXBUFFERLAYOUT_H
#define OPENGL_VERTEXBUFFERLAYOUT_H

#include <vector>
#include <GL/glew.h>
#include "Renderer.h"

struct VertexBufferElement {
    unsigned type;
    unsigned count;
    bool normalized;

    static unsigned getSizeofType(unsigned type) {
        switch (type) {  // NOLINT
            case GL_FLOAT: return 4;  // NOLINT
            case GL_UNSIGNED_INT: return 4;
            case GL_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        ASSERT(false);
        return 0;
    };
};

class VertexBufferLayout {
public:
    VertexBufferLayout();
    ~VertexBufferLayout();

    template<typename T>
    void push(unsigned count, bool normalized= false);

    inline const std::vector<VertexBufferElement>& getElements() const { return m_elements; }
    inline unsigned getStride() const { return m_stride; }


private:
    std::vector<VertexBufferElement> m_elements;
    unsigned m_stride;
};



#endif //OPENGL_VERTEXBUFFERLAYOUT_H
