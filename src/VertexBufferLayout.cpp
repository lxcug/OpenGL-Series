#include "VertexBufferLayout.h"


VertexBufferLayout::VertexBufferLayout(): m_stride(0) {

}

VertexBufferLayout::~VertexBufferLayout() = default;

template<typename T>
void VertexBufferLayout::push(unsigned count, bool normalized) {
    static_assert(true, "");
}

// 全特化push<float>
template<>
void VertexBufferLayout::push<float>(unsigned count, bool normalized) {
    m_elements.push_back({GL_FLOAT, count, false});
    m_stride += count * VertexBufferElement::getSizeofType(GL_FLOAT);
}

// 全特化push<unsigned>
template<>
void VertexBufferLayout::push<unsigned>(unsigned count, bool normalized) {
    m_elements.push_back({GL_UNSIGNED_INT, count, false});
    m_stride += count * VertexBufferElement::getSizeofType(GL_UNSIGNED_INT);
}

// 全特化push<int>
template<>
void VertexBufferLayout::push<int>(unsigned count, bool normalized) {
    m_elements.push_back({GL_INT, count, false});
    m_stride += count * VertexBufferElement::getSizeofType(GL_INT);
}

// 全特化push<unsigned char>
template<>
void VertexBufferLayout::push<unsigned char>(unsigned count, bool normalized) {
    m_elements.push_back({GL_UNSIGNED_BYTE, count, true});
    m_stride += count * VertexBufferElement::getSizeofType(GL_UNSIGNED_BYTE);
}


