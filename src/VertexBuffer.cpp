// @author: lx
// @time: 2022/9/30
// @brief:

#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    glCall(glGenBuffers(1, &m_renderer_id));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));  // bind vertex buffer
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glCall(glDeleteBuffers(1, &m_renderer_id));
}

void VertexBuffer::bind() const {
    glCall(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));  // bind vertex buffer
}

void VertexBuffer::unBind() const {
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));  // unbind vertex buffer
}

