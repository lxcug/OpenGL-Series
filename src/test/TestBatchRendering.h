// @author: lx
// @time: 2022/10/5
// @brief: 

#pragma once
#ifndef OPENGL_TESTBATCHRENDERING_H
#define OPENGL_TESTBATCHRENDERING_H

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
class TestBatchRendering : public test::Test {
    public:
        TestBatchRendering();
        explicit TestBatchRendering(TestMenu *testMenu);
        TestBatchRendering(TestMenu *testMenu, std::string windowName);
        ~TestBatchRendering() override;

        void init();

        void OnTick(float deltaTime) override;
        void onRender() override;
        void onImGuiRender() override;

    private:
        std::unique_ptr<VertexArray> m_vertexArray;
        std::unique_ptr<IndexBuffer> m_indexBuffer;
        std::unique_ptr<Shader> m_shader;
        std::unique_ptr<Texture> m_textures[2];
        std::unique_ptr<VertexBuffer> m_vertexBuffer;

        glm::mat4 m_proj, m_view;  // projection matrix and view matrix
        glm::vec3 m_translation;
        bool m_batchRender = false;  // whether to render the graphics
        ImVec4 m_clear_color;  // rgba
        float m_scale = .5f;
        float m_angle = 0.f;
    };
}


#endif //OPENGL_TESTBATCHRENDERING_H
