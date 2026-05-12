#include "window.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include <print>

namespace DG {

    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

	Window::Window(int width, int height, const char* title) 
		: m_width(width), m_height(height), m_title(title) 
	{
		(void)initializeWindow();
	}

    Window::~Window() {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    bool Window::initializeWindow() {
        if (glfwInit() == GLFW_FALSE) {
            std::println(stderr, "glfwInit() failed!");
            glfwTerminate();
            return false;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

        m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
        if (m_window == NULL) {
            std::println(stderr, "glfwCreateWindow() failed!");
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(m_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::println(stderr, "Failed to initialize GLAD");
            return false;
        }
        std::println("GL_VERSION: {}", (const char*)glGetString(GL_VERSION));

        glViewport(0, 0, m_width, m_height);
        glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

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