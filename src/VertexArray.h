// @author: lx
// @time: 2022/10/1
// @brief:

#pragma once

#ifndef OPENGL_VERTEXARRAY_H
#define OPENGL_VERTEXARRAY_H

class VertexBuffer;
class VertexBufferLayout;

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& vertexBufferLayout);

private:
    unsigned m_renderer_id;
};

#endif //OPENGL_VERTEXARRAY_H
