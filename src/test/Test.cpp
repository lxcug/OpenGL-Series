#include "Test.h"
#include "imgui.h"
#include "Renderer.h"


void test::Test::OnTick(float deltaTime) {

}

void test::Test::onRender() {

}

void test::Test::onImGuiRender() {
}

test::TestMenu::TestMenu(test::Test *&currTestPointer): m_currentTest(currTestPointer) {
}

void test::TestMenu::onImGuiRender() {
    Test::onImGuiRender();
    ImGui::Begin("Test framework");
    ImGui::TextColored(ImVec4(.45f, .75f, .85f, 1.0f), "This is a test framework");

    for(auto& test : m_tests) {
        if(ImGui::Button(test.first.c_str())) {  // if this button is clicked
            if(m_currentTest != this) {  // deal with when in subtest and click the other subtest button in the meantime
                m_currentTest->destroy();
            }
            m_currentTest = test.second();

        }
    }

    // fps
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

    if(m_useBackToMenu && ImGui::Button("back to menu") && m_currentTest != this) {
        delete m_currentTest;
        m_currentTest = this;
    }
    ImGui::End();

    if(m_currentTest != this)
        m_currentTest->onImGuiRender();
}

void test::TestMenu::OnTick(float deltaTime) {
    Test::OnTick(deltaTime);
}

void test::TestMenu::onRender() {
    Test::onRender();

    if(m_currentTest == this) {
        glCall(glClearColor(.4f, .7f, .8f, 1.f));
        glCall(glClear(GL_COLOR_BUFFER_BIT));
    }
    else {
        m_currentTest->onRender();
    }
}

