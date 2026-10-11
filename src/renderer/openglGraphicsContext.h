#include "graphicsContext.h"

#include "renderer/graphics_api.h"
#include "GLFW/glfw3.h"

#include <print>

namespace DG {

    class OpenGLGraphicsContext : public GraphicsContext {
    public:
        OpenGLGraphicsContext(GLFWwindow* windowHandle) : m_windowHandle(windowHandle) {};

        static void PreWindowCreationHints() {
#ifdef __EMSCRIPTEN__
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ES_API);
#elif __APPLE__
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
#endif
        }

        bool Initialize() override {
            glfwMakeContextCurrent(m_windowHandle);

#ifndef __EMSCRIPTEN__
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                std::println(stderr, "Failed to initialize GLAD");
                return false;
            }
#endif

            std::println("GL_VERSION: {}", (const char*)glGetString(GL_VERSION));

            //TODO: Change with 'RenderCommand', see other todo in applcation
            int width, height;
            glfwGetFramebufferSize(m_windowHandle, &width, &height);
            glViewport(0, 0, width, height);

            return true;
        }

        void SwapBuffers() override {
            glfwSwapBuffers(m_windowHandle);
        }

    private:
        GLFWwindow* m_windowHandle;
    };

}