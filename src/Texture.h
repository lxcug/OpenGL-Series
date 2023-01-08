// @author: lx
// @time: 2022/10/3
// @brief: 

#pragma once
#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include <string>
#include "Renderer.h"


class Texture {
public:
    explicit Texture(std::string fileName);
    ~Texture();

    void bind(unsigned slot=0) const;
    void unbind() const;

    inline int getHeight() const { return m_height; }
    inline int getWidth() const { return m_width; }
    inline int getBPP() const { return m_bPP; }


private:
    unsigned m_rendererId;
    std::string m_fileName;

    unsigned char* m_localBuffer;
    int m_height, m_width, m_bPP;  // bPP = bits per pixel
};

#endif //OPENGL_TEXTURE_H
