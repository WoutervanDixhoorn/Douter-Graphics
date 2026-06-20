#include "window.h"

#include "renderer/graphics_api.h"

#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <print>

namespace DG {

    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

	Window::Window(int width, int height, const char* title) 
		: m_width(width), m_height(height), m_title(title) 
	{
        if (!initializeWindow()) {
            std::println(stderr, "Failed initializing window!");
            return;
        }

        (void)initializeImGui();
	}

    Window::~Window() {
        glfwDestroyWindow(m_window);
        glfwTerminate();

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    bool Window::initializeWindow() {
        if (glfwInit() == GLFW_FALSE) {
            std::println(stderr, "glfwInit() failed!");
            glfwTerminate();
            return false;
        }

#ifdef __EMSCRIPTEN__
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ES_API);
#else
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
#endif
        m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
        if (m_window == NULL) {
            std::println(stderr, "glfwCreateWindow() failed!");
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(m_window);

#ifndef __EMSCRIPTEN__
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::println(stderr, "Failed to initialize GLAD");
            return false;
        }
#endif
        std::println("GL_VERSION: {}", (const char*)glGetString(GL_VERSION));

        glViewport(0, 0, m_width, m_height);
        glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

        return true;
	}

    bool Window::initializeImGui()
    {
        IMGUI_CHECKVERSION();
        (void)ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGui_ImplOpenGL3_Init();
        ImGui_ImplGlfw_InitForOpenGL(m_window, true);
        
        return true;
    }

    bool Window::ShouldClose() {
        return glfwWindowShouldClose(m_window);
    }

    void Window::PollAndSwap() {
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}