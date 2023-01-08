#include "TestBatchRendering.h"

#include <utility>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


test::TestBatchRendering::TestBatchRendering(): m_translation(0.f, 0.f, 0.f), m_batchRender(false),
m_clear_color(ImVec4(.4f, .7f, .8f, 1.f))
{
    init();
}

test::TestBatchRendering::TestBatchRendering(test::TestMenu *testMenu): m_translation(0.f, 0.f, 0.f), m_batchRender(false),
                                                                        m_clear_color(ImVec4(.4f, .7f, .8f, 1.f)) {
    m_testMenu = testMenu;
    init();
}

test::TestBatchRendering::TestBatchRendering(test::TestMenu *testMenu, std::string windowName): m_translation(0.f, 0.f, 0.f), m_batchRender(false),
                                                                                     m_clear_color(ImVec4(.4f, .7f, .8f, 1.f)) {
    m_testMenu = testMenu;
    m_testName = std::move(windowName);
    init();

}

void test::TestBatchRendering::init() {
    // enable blend
    glCall(glEnable(GL_BLEND));
    glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    // x y z w  r g b a texture.x texture.y texture.slot
    float vertices[] = {
            -1.f, -1.1f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            .0f, -1.1f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            .0f, .0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            -1.f, .0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

            .0f, .0f, 0.0f, 1.0f, 0.0f, .1f, 0.2f, .3f, 0.0f, 0.0f, 1.0f,
            1.0f, .0f, 0.0f, 1.0f, 0.0f, .1f, 0.2f, .3f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 0.0f, .1f, 0.2f, .3f, 1.0f, 1.0f, 1.0f,
            .0f, 1.0f, 0.0f, 1.0f, 0.0f, .1f, 0.2f, .3f, 0.0f, 1.0f, 1.0f,
    };

    m_vertexBuffer = std::make_unique<VertexBuffer>(vertices, 8 * 11 * sizeof(float));

    unsigned indices[] = {
            0, 1, 2, 2, 3, 0,
            4, 5, 6, 6, 7, 4,
    };
    m_indexBuffer = std::make_unique<IndexBuffer>(indices, 18);

    VertexBufferLayout vertexBufferLayout;
    vertexBufferLayout.push<float>(4);  // x y z w
    vertexBufferLayout.push<float>(4);  // r g b a
    vertexBufferLayout.push<float>(2);  // texture.x texture.y
    vertexBufferLayout.push<float>(1);  // texture.slot

    m_vertexArray = std::make_unique<VertexArray>();
    m_vertexArray->addBuffer(*m_vertexBuffer, vertexBufferLayout);

    m_textures[0] = std::make_unique<Texture>("../resources/textures/dog2.png");
    m_textures[1] = std::make_unique<Texture>("../resources/textures/ChernoLogo.png");

    for(int i = 0; i < 2; i++) {
        m_textures[i]->bind(i);
    }

    int samplers[2] = {0, 1};
    m_shader = std::make_unique<Shader>("../resources/shaders/batchVertexShader.shader",
                                        "../resources/shaders/batchFragmentShader.shader");
    m_shader->bind();
    m_shader->setUniform1iv("u_textures", 2, samplers);
}

test::TestBatchRendering::~TestBatchRendering() {

}

void test::TestBatchRendering::OnTick(float deltaTime) {
    Test::OnTick(deltaTime);
}

void test::TestBatchRendering::onRender() {
    Test::onRender();

    glClearColor(m_clear_color.x * m_clear_color.w, m_clear_color.y * m_clear_color.w,
                 m_clear_color.z * m_clear_color.w, m_clear_color.w);
    glCall(glClear(GL_COLOR_BUFFER_BIT));

    if(m_batchRender) {
        // projected matrix
        m_proj = glm::ortho(-1.8f, 1.8f, -1.5f, 1.5f, -1.f, 1.f);
        m_view = glm::translate(glm::mat4(1.f), glm::vec3(-0.f, 0.f, 0.f));

        glm::mat4 model = glm::translate(glm::mat4(.1f), m_translation);
        model *= glm::scale(glm::mat4(1.f), glm::vec3(m_scale, m_scale, m_scale));  // 缩放
        model *= glm::rotate(glm::mat4(1.f), m_angle, glm::vec3(.0f, .0f, 1.0f));  // rotation

        glm::mat4 mvp = m_proj * m_view * model;
        m_shader->setUniformMat4f("u_modelViewProjection", mvp);

        m_shader->bind();
        Renderer renderer;
        renderer.draw(*m_vertexArray, *m_indexBuffer, *m_shader);
    }
}

void test::TestBatchRendering::onImGuiRender() {
    Test::onImGuiRender();
    ImGui::Begin(m_testName.c_str());
    if(ImGui::Button("<-")) {
        m_testMenu->m_currentTest = m_testMenu;
        destroy();
    }
    ImGui::Checkbox("batch rendering", &m_batchRender);

    ImGui::ColorEdit4("Clear color", (float*)&m_clear_color);
    // control translation
    ImGui::SliderFloat3("translation", &m_translation.x, -1.0f, 1.0f);

    // control scale
    ImGui::SliderFloat("scale", &m_scale, 0.f, 2.f);

    // control rotation
    ImGui::SliderFloat("rotation", &m_angle, 0.f, 10.f);

    // fps
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

    ImGui::End();
}


