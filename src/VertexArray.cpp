// @author: lx
// @time: 2022/10/1
// @brief:

#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


VertexArray::VertexArray() {
    glCall(glGenVertexArrays(1, &m_renderer_id));
}

VertexArray::~VertexArray() {
    glCall(glDeleteVertexArrays(1, &m_renderer_id));
}

void VertexArray::bind() const {
    glCall(glBindVertexArray(m_renderer_id));
}

void VertexArray::unbind() const {
    glCall(glBindVertexArray(0));
}


void VertexArray::addBuffer(const VertexBuffer &vertexBuffer, const VertexBufferLayout &vertexBufferLayout) {
    this->bind();
    vertexBuffer.bind();

    const auto& elements = vertexBufferLayout.getElements();
    unsigned offset = 0;
    for(unsigned i = 0; i < elements.size(); i++) {
        const auto &element = elements[i];
        glCall(glEnableVertexAttribArray(i));
        glCall(glVertexAttribPointer(i, element.count, element.type, element.normalized,
                                     vertexBufferLayout.getStride(), (const void *) offset));
        offset += element.count * VertexBufferElement::getSizeofType(element.type);
    }
}
