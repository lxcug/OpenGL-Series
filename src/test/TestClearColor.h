// @author: lx
// @time: 2022/10/4
// @brief: 

#pragma once
#ifndef OPENGL_TESTCLEARCOLOR_H
#define OPENGL_TESTCLEARCOLOR_H

#include "Test.h"

namespace test {
    class TestClearColor : public test::Test {
    public:
        TestClearColor();
        explicit TestClearColor(TestMenu* testMenu);
        TestClearColor(TestMenu* testMenu, std::string windowName);
        ~TestClearColor() override = default;

        void OnTick(float deltaTime) override;
        void onRender() override;
        void onImGuiRender() override;

    private:
        float m_clearColor[4];
    };
}

#endif //OPENGL_TESTCLEARCOLOR_H
