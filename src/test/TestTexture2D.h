// @author: lx
// @time: 2022/10/4
// @brief: 

#pragma once
#ifndef OPENGL_TESTTEXTURE2D_H
#define OPENGL_TESTTEXTURE2D_H

#include <memory>

#include "Test.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "imgui.h"


namespace test {
    class TestTexture2D : public test::Test {
    public:
        TestTexture2D();
        explicit TestTexture2D(TestMenu* testMenu);
        TestTexture2D(TestMenu* testMenu, std::string windowName);
        ~TestTexture2D() override;
        void init();

        void OnTick(float deltaTime) override;
        void onRender() override;
        void onImGuiRender() override;

    private:
        std::unique_ptr<VertexArray> m_vertexArray;
        std::unique_ptr<IndexBuffer> m_indexBuffer;
        std::unique_ptr<Shader> m_shader;
        std::unique_ptr<Texture> m_texture;
        std::unique_ptr<VertexBuffer> m_vertexBuffer;

        glm::mat4 m_proj, m_view;  // projection matrix and view matrix
        glm::vec3 m_translation1, m_translation2;
        bool m_render = false;  // whether to render the graphics
        ImVec4 m_clear_color;  // rgba
    };
}

#endif //OPENGL_TESTTEXTURE2D_H
