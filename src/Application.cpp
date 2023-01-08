//
// Created by hustlx on 2022/9/30.
//

#define GLEW_STATIC
#define GL_SILENCE_DEPRECATION
#include <GL/glew.h>  // 必须在glfw之前
#include <GLFW/glfw3.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "stb_image/stb_image.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// imgui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "test/TestClearColor.h"
#include "test/TestTexture2D.h"
#include "test/TestBatchRendering.h"

static void HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main() {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    GLFWwindow* window = glfwCreateWindow(1280, 760, "OpenGL", nullptr, nullptr);
    glfwSetWindowPos(window, 800, 400);
    if(!window) {
        glfwTerminate();
        return -1;
    }

    GLFWimage img;
    img.width = 48;
    img.height = 48;
    size_t buffer_size = img.height * img.width * 4;
    int bpp;
    auto* icon_buffer = stbi_load("../resources/img.png", &img.width, &img.height, &bpp, 4);
    img.pixels = icon_buffer;
    glfwSetWindowIcon(window, 1, &img);
    if(icon_buffer) {
        stbi_image_free(icon_buffer);
    }


    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // Enable vsync
    if(glewInit() != GLEW_OK) {  // glewInit must be invoked behind glfwMakeContextCurrent
        std::cout << "glew error\n";
        return -1;
    }

    {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.Fonts->AddFontFromFileTTF("../resources/fonts/consolas.ttf", 17.f, nullptr);

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImGui::StyleColorsDark();

        const char* glsl_version = "#version 410";
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        auto* testMenu = new test::TestMenu();
        testMenu->registerTest<test::TestClearColor>("Clear color");
        testMenu->registerTest<test::TestTexture2D>("2D texture");
        testMenu->registerTest<test::TestBatchRendering>("batch rendering");

        while(!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            testMenu->OnTick(1);
            testMenu->onRender();
            testMenu->onImGuiRender();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                GLFWwindow* backup_current_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }

            glfwSwapBuffers(window);
        }
    }
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

