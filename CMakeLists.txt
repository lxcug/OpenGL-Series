cmake_minimum_required(VERSION 3.14)
project(opengl)

set(CMAKE_CXX_STANDARD 14)

include_directories(dependencies)
include_directories(dependencies/GLFW)  # GLFW
include_directories(dependencies/glew-2.1.0/include)  # glew
include_directories(dependencies/glad/include)  # glad  -- not used
include_directories(src/vendor)
include_directories(src/vendor/imgui)
include_directories(src/vendor/imgui/example_glfw_opengl3)
include_directories(src)
include_directories(src/vendor/imgui/backends)

add_executable(dx11_demo src/vendor/imgui/examples/example_win32_directx11/main.cpp
        src/vendor/imgui/imgui.h src/vendor/imgui/imgui.cpp
        src/vendor/imgui/imconfig.h
        src/vendor/imgui/imgui_draw.cpp
        src/vendor/imgui/imgui_internal.h
        src/vendor/imgui/imgui_tables.cpp
        src/vendor/imgui/imgui_widgets.cpp
        src/vendor/imgui/backends/imgui_impl_glfw.h
        src/vendor/imgui/backends/imgui_impl_glfw.cpp
        src/vendor/imgui/backends/imgui_impl_opengl3.h
        src/vendor/imgui/backends/imgui_impl_opengl3.cpp
        src/vendor/imgui/imgui_demo.cpp
        )

add_executable(demo src/vendor/imgui/examples/example_glfw_opengl3/main.cpp
        src/vendor/imgui/imgui.h src/vendor/imgui/imgui.cpp
        src/vendor/imgui/imconfig.h
        src/vendor/imgui/imgui_draw.cpp
        src/vendor/imgui/imgui_internal.h
        src/vendor/imgui/imgui_tables.cpp
        src/vendor/imgui/imgui_widgets.cpp
        src/vendor/imgui/backends/imgui_impl_glfw.h
        src/vendor/imgui/backends/imgui_impl_glfw.cpp
        src/vendor/imgui/backends/imgui_impl_opengl3.h
        src/vendor/imgui/backends/imgui_impl_opengl3.cpp
        src/vendor/imgui/imgui_demo.cpp
        )

add_executable(Application src/Application.cpp
        src/Renderer.h src/Renderer.cpp
        src/VertexBuffer.cpp src/VertexBuffer.h
        src/IndexBuffer.cpp
        src/IndexBuffer.h
        src/VertexArray.cpp src/VertexArray.h
        src/VertexBufferLayout.cpp src/VertexBufferLayout.h
        src/Shader.cpp src/Shader.h
        src/vendor/stb_image/stb_image.h src/vendor/stb_image/stb_image.cpp
        src/Texture.cpp src/Texture.h

        src/vendor/imgui/imgui.h src/vendor/imgui/imgui.cpp
        src/vendor/imgui/imconfig.h
        src/vendor/imgui/imgui_draw.cpp
        src/vendor/imgui/imgui_internal.h
        src/vendor/imgui/imgui_tables.cpp
        src/vendor/imgui/imgui_widgets.cpp
        src/vendor/imgui/backends/imgui_impl_glfw.h
        src/vendor/imgui/backends/imgui_impl_glfw.cpp
        src/vendor/imgui/backends/imgui_impl_opengl3.h
        src/vendor/imgui/backends/imgui_impl_opengl3.cpp
        src/vendor/imgui/imgui_demo.cpp
        src/test/Test.cpp src/test/Test.h
        src/test/TestClearColor.cpp src/test/TestClearColor.h
        src/test/TestTexture2D.cpp src/test/TestTexture2D.h src/test/TestBatchRendering.cpp src/test/TestBatchRendering.h)


target_link_libraries(demo
        ${PROJECT_SOURCE_DIR}/dependencies/glfw-3.3.8.bin.WIN64/lib-mingw-w64/libglfw3.a
        ${PROJECT_SOURCE_DIR}/dependencies/glew-2.1.0/lib/Release/x64/glew32s.lib
        opengl32.dll
        )

target_link_libraries(Application
        ${PROJECT_SOURCE_DIR}/dependencies/glfw-3.3.8.bin.WIN64/lib-mingw-w64/libglfw3.a
        ${PROJECT_SOURCE_DIR}/dependencies/glew-2.1.0/lib/Release/x64/glew32s.lib
        opengl32.dll
        )

target_link_libraries(dx11_demo
        ${PROJECT_SOURCE_DIR}/dependencies/glfw-3.3.8.bin.WIN64/lib-mingw-w64/libglfw3.a
        ${PROJECT_SOURCE_DIR}/dependencies/glew-2.1.0/lib/Release/x64/glew32s.lib
        opengl32.dll
        )

add_executable(test test.cpp)