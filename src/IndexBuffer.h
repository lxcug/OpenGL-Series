// @author: lx
// @time: 2022/9/30
// @brief:

#pragma once

#ifndef OPENGL_INDEXBUFFER_H
#define OPENGL_INDEXBUFFER_H

class IndexBuffer {
public:
    IndexBuffer(const unsigned* data, unsigned count);
    ~IndexBuffer();

    void bind() const;
    void unBind() const;
    unsigned getCount() const {
        return m_count;
    }

private:
    unsigned m_renderer_id;
    unsigned m_count;
};

#endif //OPENGL_INDEXBUFFER_H
