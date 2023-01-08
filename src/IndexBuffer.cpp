// @author: lx
// @time: 2022/9/30
// @brief:

#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned* data, unsigned int count): m_count(count) {
    glCall(glGenBuffers(1, &m_renderer_id))
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));  // bind index buffer
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    glCall(glDeleteBuffers(1, &m_renderer_id));
}

void IndexBuffer::bind() const {
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));  // bind index buffer
}

void IndexBuffer::unBind() const {
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));  // unbind index buffer
}

