// @author: lx
// @time: 2022/10/4
// @brief: 

#pragma once
#ifndef OPENGL_TEST_H
#define OPENGL_TEST_H

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <memory>


namespace test {
    class TestMenu;
    class Test {
    public:
        Test() = default;
        virtual ~Test() {}

        // only Test object allocates on heap memory can invoke destroy function
        virtual void destroy() { std::cout << "reclaim memory of test object\n"; delete this; }

        virtual void OnTick(float deltaTime);
        virtual void onRender();
        virtual void onImGuiRender();

    protected:
        TestMenu* m_testMenu;  // don't need to reclaim memory cause it's only a pointer to the menu
        std::string m_testName = "test";
    };

    class Test;
    class TestMenu : public Test {
    public:
        TestMenu(): m_currentTest(this) {}
        explicit TestMenu(Test*& currTestPointer);
        ~TestMenu() override {
            if(m_currentTest != this) {  // don't delete itself
                delete m_currentTest;
            }
        }

        void OnTick(float deltaTime) override;
        void onRender() override;
        void onImGuiRender() override;

        void setAddBackToMenu(bool flag) { m_useBackToMenu = flag; }

        template<typename T>
        void registerTest(const std::string& label) {
            std::cout << "Register test " << label << std::endl;
            m_tests.push_back(std::make_pair(label, [this, label]() { return new T(this, label); }));
        }

        Test* m_currentTest;
        std::vector<std::pair<std::string, std::function<Test*()>>> m_tests;
        bool m_useBackToMenu = false;
    };
}


#endif //OPENGL_TEST_H
