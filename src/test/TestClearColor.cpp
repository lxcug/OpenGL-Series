#include "TestClearColor.h"

#include "Renderer.h"
#include "imgui/imgui.h"

test::TestClearColor::TestClearColor(): m_clearColor {.4f, .7f, .8f, 1.f} {

}

test::TestClearColor::TestClearColor(test::TestMenu *testMenu): m_clearColor {.4f, .7f, .8f, 1.f} {
    m_testMenu = testMenu;
}

test::TestClearColor::TestClearColor(test::TestMenu *testMenu, std::string windowName): m_clearColor {.4f, .7f, .8f, 1.f} {
    m_testMenu = testMenu;
    m_testName = std::move(windowName);
}

void test::TestClearColor::OnTick(float deltaTime) {
    Test::OnTick(deltaTime);
}

void test::TestClearColor::onRender() {
    Test::onRender();
    glCall(glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
    glCall(glClear(GL_COLOR_BUFFER_BIT));
}

void test::TestClearColor::onImGuiRender() {
    Test::onImGuiRender();
    ImGui::Begin(m_testName.c_str());
    if(ImGui::Button("<-")) {
        m_testMenu->m_currentTest = m_testMenu;
        destroy();
    }
    ImGui::ColorEdit4("Clear color", m_clearColor);
    // fps
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::End();
}





