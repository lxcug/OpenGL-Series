// @author: lx
// @time: 2022/9/30
// @brief:

#pragma once

#ifndef OPENGL_VERTEXBUFFER_H
#define OPENGL_VERTEXBUFFER_H

class VertexBuffer {
public:
    VertexBuffer(const void* data, unsigned size);
    ~VertexBuffer();

    void bind() const;
    void unBind() const;

private:
    unsigned m_renderer_id;
};

#endif //OPENGL_VERTEXBUFFER_H
