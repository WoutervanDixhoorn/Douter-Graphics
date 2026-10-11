#include "window.h"

#include "renderer/openglGraphicsContext.h"
#include "application.h"

#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <print>

namespace DG {

	Window::Window(int width, int height, const char* title) 
		: m_width(width), m_height(height), m_title(title)
	{
	    if (!initializeWindow()) {
            std::println(stderr, "Failed initializing window!");
            return;
        }

	    m_context = std::make_unique<OpenGLGraphicsContext>(m_window);
        m_context->Initialize();

	    (void)initializeCallbacks();
        (void)initializeImGui();
	}

    Window::~Window() {
        glfwDestroyWindow(m_window);
        glfwTerminate();

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void Window::SetEventCallback(std::function<void(IEvent&)> callback) {
        m_data.eventCallback = callback;
    }

    bool Window::initializeWindow() {
        if (glfwInit() == GLFW_FALSE) {
            std::println(stderr, "glfwInit() failed!");
            glfwTerminate();
            return false;
        }

	    OpenGLGraphicsContext::PreWindowCreationHints();

        m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
        if (m_window == NULL) {
            std::println(stderr, "glfwCreateWindow() failed!");
            glfwTerminate();
            return false;
        }

        glfwSetWindowUserPointer(m_window, &m_data);

        return true;
	}

    bool Window::initializeCallbacks() {
        glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            auto&[eventCallback] = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            if (action == GLFW_PRESS) {
                KeyPressedEvent keyEvent(key);
                eventCallback(keyEvent);
            } else if (action == GLFW_RELEASE) {
                KeyReleasedEvent keyEvent(key);
                eventCallback(keyEvent);
            }
        });

        glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x, double y) {
            auto&[eventCallback] = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            MouseMovedEvent mouseMovedEvent(x, y);
            eventCallback(mouseMovedEvent);
        });

	    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
	        auto&[eventCallback] = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

	        if (action == GLFW_PRESS) {
	            MousePressedEvent pressedEvent(button);
	            eventCallback(pressedEvent);
	        } else if (action == GLFW_RELEASE) {
	            MouseReleasedEvent releasedEvent(button);
	            eventCallback(releasedEvent);
	        }
	    });

	    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
            auto&[eventCallback] = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            WindowResizeEvent resizeEvent(width, height);
            eventCallback(resizeEvent);
        });

	    glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
	        auto&[eventCallback] = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

	        WindowCloseEvent closeEvent;
	        eventCallback(closeEvent);
	    });

	    glfwSetWindowIconifyCallback(m_window, [](GLFWwindow* window, int iconified) {
	        auto&[eventCallback] = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

	    	if (iconified) {
				WindowMinimizeEvent minimizeEvent(true);
	    		eventCallback(minimizeEvent);
	    	} else {
				WindowMinimizeEvent unminimizeEvent(false);
	    		eventCallback(unminimizeEvent);
	    	}
	    });

		glfwSetWindowMaximizeCallback(m_window, [](GLFWwindow* window, int maximized) {
			auto&[eventCallback] = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			if (maximized) {
				WindowMaximizeEvent maximizedEvent(true);
				eventCallback(maximizedEvent);
			} else {
				WindowMaximizeEvent unmaximizedEvent(false);
				eventCallback(unmaximizedEvent);
			}
		});

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

    void Window::PollEvents() {
        glfwPollEvents();
    }

    void Window::SwapBuffers() {
        m_context->SwapBuffers();
    }

}