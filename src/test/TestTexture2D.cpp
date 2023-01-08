#include "TestTexture2D.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


test::TestTexture2D::TestTexture2D(): m_translation1(0.f, 0.f, 0.f), m_translation2(0.f, 0.f, 0.f),
                                      m_render(false), m_clear_color(ImVec4(.4f, .7f, .8f, 1.f)) {
   init();
}

test::TestTexture2D::TestTexture2D(test::TestMenu *testMenu): m_translation1(0.f, 0.f, 0.f), m_translation2(0.f, 0.f, 0.f),
                                                              m_render(false), m_clear_color(ImVec4(.4f, .7f, .8f, 1.f)) {
    m_testMenu = testMenu;
    init();
}

test::TestTexture2D::TestTexture2D(test::TestMenu *testMenu, std::string windowName): m_translation1(0.f, 0.f, 0.f), m_translation2(0.f, 0.f, 0.f),
                                                                           m_render(false), m_clear_color(ImVec4(.4f, .7f, .8f, 1.f)) {
    m_testMenu = testMenu;
    m_testName = std::move(windowName);
    init();
}

void test::TestTexture2D::init() {
    // enable blend
    glCall(glEnable(GL_BLEND));
    glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    float positions[] = {
            -1.f, -1.2f, .0f, .0f,
            1.f, -1.2f, 1.f, 0.f,
            1.f, 1.2f, 1.f, 1.f,
            -1.f, 1.2f, 0.f, 1.f
    };

    // vertex buffer
    m_vertexBuffer = std::make_unique<VertexBuffer>(positions, 16*sizeof(float));

    // vertex array
    VertexBufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(2);

    // indices buffer
    unsigned indices[] = {
            0, 1, 2,
            2, 3, 0
    };
    m_indexBuffer = std::make_unique<IndexBuffer>(indices, 6);
    m_vertexArray = std::make_unique<VertexArray>();
    m_vertexArray->addBuffer(*m_vertexBuffer, layout);

    // texture
    m_texture = std::make_unique<Texture>("../resources/textures/dog2.png");

    // shader
    m_shader = std::make_unique<Shader>("../resources/shaders/vertexShader.shader",
                                        "../resources/shaders/fragmentShader.shader");
}


test::TestTexture2D::~TestTexture2D() = default;

void test::TestTexture2D::OnTick(float deltaTime) {
    Test::OnTick(deltaTime);
}

void test::TestTexture2D::onRender() {
    Test::onRender();
    glClearColor(m_clear_color.x * m_clear_color.w, m_clear_color.y * m_clear_color.w,
                 m_clear_color.z * m_clear_color.w, m_clear_color.w);
    glCall(glClear(GL_COLOR_BUFFER_BIT));

    // projected matrix
    m_proj = glm::ortho(-1.8f, 1.8f, -1.5f, 1.5f, -1.f, 1.f);
    m_view = glm::translate(glm::mat4(1.f), glm::vec3(-0.f, 0.f, 0.f));

    Renderer renderer;
    m_texture->bind(0);

    if(m_render) {
        {
            glm::mat4 model = glm::translate(glm::mat4(.1f), m_translation1);
            glm::mat4 mvp = m_proj * m_view * model;
            m_shader->bind();
            m_shader->setUniformMat4f("u_modelViewProjection", mvp);
            renderer.draw(*m_vertexArray, *m_indexBuffer, *m_shader);
        }
        {
            glm::mat4 model = glm::translate(glm::mat4(.1f), m_translation2);
            glm::mat4 mvp = m_proj * m_view * model;
            m_shader->bind();
            m_shader->setUniformMat4f("u_modelViewProjection", mvp);
            renderer.draw(*m_vertexArray, *m_indexBuffer, *m_shader);
        }
    }
}

void test::TestTexture2D::onImGuiRender() {
    Test::onImGuiRender();

    ImGui::Begin(m_testName.c_str());
    if(ImGui::Button("<-")) {
        m_testMenu->m_currentTest = m_testMenu;
        destroy();
    }
    ImGui::Checkbox("render", &m_render);

    ImGui::ColorEdit4("Clear color", (float*)&m_clear_color);

    // control translation
    ImGui::SliderFloat3("translation1", &m_translation1.x, -1.0f, 1.0f);
    ImGui::SliderFloat3("translation2", &m_translation2.x, -1.0f, 1.0f);

    // fps
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

    ImGui::End();
}



