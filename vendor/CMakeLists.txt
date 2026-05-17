cmake_minimum_required(VERSION 3.26)

# GLAD configureren
add_library(glad STATIC
    glad/src/glad.c
)
target_include_directories(glad PUBLIC 
    glad/include
)

# ImGui configureren
set(IMGUI_SOURCES
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_tables.cpp
	imgui/imgui_demo.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC 
    imgui
    imgui/backends
)

target_link_libraries(imgui PRIVATE glfw)